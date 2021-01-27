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



SET "Dflags=-DTCC_TARGET_PE -DTCC_TARGET_X86_64"




:Compilation
ECHO 1. TCC Library is being compiled.. 
ECHO  Source File: ..\libtcc.c 
ECHO  Output Files: libtcc.dll, libtcc.def
ECHO  Preprocessor Flags: -shared %Dflags% -DLIBTCC_AS_DLL 
ECHO ___________________________________________________ 
%CC% -shared "..\libtcc.c" %Dflags% -DLIBTCC_AS_DLL -o "libtcc.dll"
IF ERRORLEVEL 1 (
	ECHO [-] Unable To Compile: TCC Library: libtcc.dll
) ELSE ECHO [+] TCC Library is Compiled Successfuly.
ECHO.

ECHO 2. TCC Executable is being compiled.. 
ECHO  Source File: ..\tcc.c
ECHO  Preprocessor Flags: %Dflags% -DONE_SOURCE"=0"
ECHO  Explanation: -DONE_SOURCE"=0" is used to link tcc.exe to libtcc.dll and reuse it. Can be ommited, but saves disk space.
ECHO ___________________________________________________
%CC%  ..\tcc.c libtcc.dll %Dflags% -DONE_SOURCE"=0" -o "tcc.exe"
IF ERRORLEVEL 1 (
	ECHO [-] Unable To Compile: TCC Executable: tcc.exe
) ELSE ECHO [+] TCC Executable: tcc.exe is Compiled Successfuly.

PAUSE
REM ECHO Now we need -DONE_SOURCE"=0" option to test what it does.
REM ECHO I think that it is simply make libtcc.dll library usable with multiple architectures 
REM ECHO (With both TCC.exe x32 and x64)
REM pause
