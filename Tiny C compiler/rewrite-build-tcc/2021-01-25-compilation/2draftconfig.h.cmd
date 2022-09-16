@ECHO OFF

FOR %%I in (.) DO SET "thisFolder=%%~nxI"
IF NOT "%thisFolder%" == "win32" (
	ECHO Please place/move/copy this script file inside win32 folder of TCC source code.
	ECHO Example: "tinycc-HEAD-d0d0c8b\win32\%~nx0"
	PAUSE

 )

:config.h

REM Can be seen via "tcc -version"
set /p VERSION= < ..\VERSION 
REM Writes a new config.h
(
  ECHO #define TCC_VERSION "%VERSION% (Compiled at: %DATE: =0%)"
  ECHO #ifdef TCC_TARGET_X86_64
  ECHO #define TCC_LIBTCC1 "libtcc1-64.a"
  ECHO #else
  ECHO #define TCC_LIBTCC1 "libtcc1-32.a"
  ECHO #endif
) > "..\config.h"

REM removes old tcc.exe and tcc.dll in tinycc-HEAD-1ed4b6b\win32\
REM for %%f in (*tcc.exe *tcc.dll) do @del %%f

SET "PATH=%CD%\..\..\tcc;%PATH%"
SET "CC=%CD%\..\..\tcc\tcc.exe"
REM Used to be: SET "CC=tcc"
REM But after first build, tcc.exe will be targeted in tinycc-HEAD-1ed4b6b\win32 instead of \..\..\tcc.exe
REM Leading to an error "<command line>:10: error: include file 'tccdefs.h' not found"
REM which means that the newly compiled tcc.exe is being used in the current directory


REM multiple architectures compilation
REM primary architecture build
REM secondary architecture build


REM DflagsForX64
REM DflagsForX32
REM FilenameforX32  i386-win32
REM FilenameforX64  x86_64-win32
SET "DflagsSecondary=-DTCC_TARGET_PE -DTCC_TARGET_X86_64"
SET "Dflags=-DTCC_TARGET_PE -DTCC_TARGET_I386"
SET "prefix-architecture=i386-win32"
SET "prefix-architecture=x86_64-win32"

REM outputDir Examples: 
REM          ..\                 - Lower level Directory
REM          .\                  - Current directory of the Command Prompt (Default)
REM          .\randoom\          - "randoom" named directory In the Current Directory
REM %USERPROFILE%\Desktop\output - In an "output" folder inside "Desktop" of the Current user.
REM          %~dp0\              - Current Directory of this executable script file. 

REM Common Mistakes:  
REM FIXED:   .\randoom   instead of  .\randoom\   - Appends a name "randoom" to the output filenames.

SET "outputDir=%USERPROFILE%\Desktop\output"
MKDIR "%outputDir%" 2>NUL & IF ERRORLEVEL 1 (
	ECHO|SET /p="[INFO-NOTICE] MKDIR: "
	MKDIR "%outputDir%"
	ECHO.
)

ECHO General Output directory: %outputDir%

:Compilation
ECHO ____________________________Main-Compilation_____________________________            
ECHO   TCC Library is being compiled!
ECHO   ^| Source File: ..\libtcc.c
ECHO   ^| Output Files: libtcc.dll, libtcc.def
ECHO   ^| Preprocessor Flags: -shared %Dflags% -DLIBTCC_AS_DLL 
"%CC%" -shared "..\libtcc.c" %Dflags% -DLIBTCC_AS_DLL -o "%outputDir%\libtcc.dll"
IF ERRORLEVEL 1 (
	ECHO  [-] Unable To Compile: TCC Library: libtcc.dll
	IF NOT EXIST "%CC%" ( 
		ECHO     [-] The TCC compiler has not been found here: 
		ECHO         "%CC%"
		)
	ECHO      [?] Current Directory: %CD%
) ELSE (
	ECHO   TCC Library libtcc.dll is Compiled Successfuly.
)
ECHO.
ECHO   TCC Executable is being compiled!
ECHO   ^| Source File: ..\tcc.c
ECHO   ^| Output Files: tcc.exe
ECHO   ^| Preprocessor Flags: %Dflags% -DONE_SOURCE"=0"
REM    Explanation: -DONE_SOURCE"=0" is used to link tcc.exe to libtcc.dll and reuse it. 
REM                (-DONE_SOURCE"=0" Can be ommited, flag is only used to reduce size)

:: Bug Found, -run |  Compiling with an old/previous libtcc library, everything is alright (FROM Bellards official site). A newly compiled library says that -run is not available(%outputDir%\libtcc.dll)
"%CC%"  "..\tcc.c" "%outputDir%\libtcc.dll" %Dflags% -DONE_SOURCE"=0" -o "%outputDir%\tcc.exe"
IF ERRORLEVEL 1 (
	ECHO  Unable To Compile: TCC Executable: tcc.exe
) ELSE (
	ECHO   TCC Executable  tcc.exe is Compiled Successfuly.
	
	
	("%outputDir%\tcc" "-run"  2>&1  | findstr /N /A:4E /c:"-run is not available in a cross compiler" ) >NUL
	IF ERRORLEVEL 1 (
		ECHO No Error
	) ELSE (
		ECHO There is Error: -run is not available in a cross compiler
		ECHO Running x32 compiler on x86-64 Windows OS gives this error.
		ECHO Please use x86-64 version instead of x32 compiler on x64 system.
		ECHO OR compile with -DTCC_IS_NATIVE flag to compile according to your computer's architecture.
	)

PAUSE

ECHO.
ECHO   Alternative TCC Executable is being compiled! 
ECHO   ^| Source File: ..\tcc.c 
ECHO   ^| Output Files: %prefix-architecture%-tcc.exe
ECHO   ^| Preprocessor Flags: %DflagsSecondary%
:: Bug Found, -run |  Compiling with an old/previous libtcc library, everything is alright (FROM Bellards official site). A newly compiled library says that -run is not available (%outputDir%\libtcc.dll)
%CC% "..\tcc.c" "%outputDir%\libtcc.dll" %DflagsSecondary% -o "%outputDir%\%prefix-architecture%-tcc.exe"
IF ERRORLEVEL 1 ( 
	ECHO  Unable To Compile: TCC Secondary Executable: %prefix-architecture%-tcc.exe
) ELSE (
	ECHO   TCC Secondary Executable: %prefix-architecture%-tcc.exe is Compiled Successfuly.
)
ECHO.

ECHO ___________________________Creating Directories___________________________  

REM EXES_ONLY

REM "Folder ok" means Okey, a playful indication that it is ok. (^__^)
REM Originally, MKDIR did not log/show messages of the Sucessfull attempts, only Error text output. 
ECHO Creating directories..
FOR %%D IN (libtcc lib doc include examples) DO (
	IF NOT EXIST "%outputDir%\%%D"   ( MKDIR "%outputDir%\%%D"   & IF ERRORLEVEL 0 ECHO  Sucessfully created "%outputDir%\%%D"   ) ELSE ECHO  Folder ok "%outputDir%\%%D"  Already exist 	
)

ECHO.
ECHO __________________Copy .h Headers and .def files, .txt files_______________


REM  [Generating .def file] 
REM  [No more Needed, for historical reference only] [Backwards comptibility]
REM  When compiling TCC Library, libtcc.c - already makes one.
REM
REM  Description:   Makes .def file from libtcc.dll library
REM                 Using -impdef source code from tcctools.c that is recently included in the tcc.exe binary itself.

IF NOT EXIST "%outputDir%\libtcc.def" (
	ECHO Making a .def file from TCC Library (libtcc.dll)
	"%outputDir%\tcc.exe" -impdef "%outputDir%\libtcc.dll" -o "%outputDir%\libtcc.def"
	IF ERRORLEVEL 1 (
		ECHO An Error occured while making "libtcc.def" file out of "libtcc.dll" using "tcc.exe -impdef"
		PAUSE
	)
)

REM [Definition files .def]
MOVE "%outputDir%\libtcc.def" "%outputDir%\libtcc\"


REM [Header files .h]
ECHO. 
COPY "..\include\*.h"         "%outputDir%\include"
COPY "..\tcclib.h"            "%outputDir%\include"
COPY "..\libtcc.h"            "%outputDir%\libtcc"
COPY "..\tests\libtcc_test.c" "%outputDir%\examples"
COPY "tcc-win32.txt"          "%outputDir%\doc"

ECHO.
ECHO _____________Compiling TCC runtime library and other libraries____________  
ECHO libtcc1.c

ECHO.
ECHO  TIP: %%EXES_ONLY%% simply jumps over Header files being included and compilation of further libraries.
ECHO  Skips any Documentation and Deletes *.o *.def files created.

PAUSE
REM ECHO Now we need -DONE_SOURCE"=0" option to test what it does.
REM ECHO I think that it is simply make libtcc.dll library usable with multiple architectures 
REM ECHO (With both TCC.exe x32 and x64)
REM pause
