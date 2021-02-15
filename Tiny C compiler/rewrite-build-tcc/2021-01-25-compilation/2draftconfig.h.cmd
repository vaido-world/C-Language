@ECHO OFF

:config.h
REM Writes a new config.h
(
  ECHO #define TCC_VERSION "%VERSION%"
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
                                
ECHO   TCC Library is being compiled!
ECHO   ^| Source File: ..\libtcc.c
ECHO   ^| Output Files: libtcc.dll, libtcc.def
ECHO   ^| Preprocessor Flags: -shared %Dflags% -DLIBTCC_AS_DLL 
%CC% -shared "..\libtcc.c" %Dflags% -DLIBTCC_AS_DLL -o "%outputDir%\libtcc.dll"
IF ERRORLEVEL 1 (
	ECHO  [-] Unable To Compile: TCC Library: libtcc.dll
	PAUSE
) ELSE ECHO   TCC Library libtcc.dll is Compiled Successfuly.
ECHO.
ECHO   TCC Executable is being compiled!
ECHO   ^| Source File: ..\tcc.c
ECHO   ^| Output Files: tcc.exe
ECHO   ^| Preprocessor Flags: %Dflags% -DONE_SOURCE"=0"
REM    Explanation: -DONE_SOURCE"=0" is used to link tcc.exe to libtcc.dll and reuse it. 
REM                (-DONE_SOURCE"=0" Can be ommited, flag is only used to reduce size)
%CC%  "..\tcc.c" "libtcc.dll" %Dflags% -DONE_SOURCE"=0" -o "%outputDir%\tcc.exe"
IF ERRORLEVEL 1 (
	ECHO  Unable To Compile: TCC Executable: tcc.exe
	PAUSE
) ELSE  ECHO   TCC Executable  tcc.exe is Compiled Successfuly.
ECHO.
ECHO   Alternative TCC Executable is being compiled! 
ECHO   ^| Source File: ..\tcc.c 
ECHO   ^| Output Files: %prefix-architecture%-tcc.exe
ECHO   ^| Preprocessor Flags: %DflagsSecondary%

%CC% "..\tcc.c" %DflagsSecondary% -o "%outputDir%\%prefix-architecture%-tcc.exe"
IF ERRORLEVEL 1 ( 
	ECHO  Unable To Compile: TCC Secondary Executable: %prefix-architecture%-tcc.exe
	PAUSE
) ELSE ECHO   TCC Secondary Executable: %prefix-architecture%-tcc.exe is Compiled Successfuly.
ECHO.


ECHO  TIP: %%EXES_ONLY%% simply jumps over Header files being included and compilation of further libraries.
ECHO  Skips any Documentation and Deletes *.o *.def files created.

PAUSE
REM ECHO Now we need -DONE_SOURCE"=0" option to test what it does.
REM ECHO I think that it is simply make libtcc.dll library usable with multiple architectures 
REM ECHO (With both TCC.exe x32 and x64)
REM pause
