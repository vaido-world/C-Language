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
for %%f in (*tcc.exe *tcc.dll) do @del %%f

SET "PATH=%CD%\tcc;%PATH%"
SET "CC=tcc"


SET "Dflags=-DTCC_TARGET_PE -DTCC_TARGET_X86_64"

:Compilation
ECHO [+] TCC Library is being compiled.. 
ECHO  Source File: ..\libtcc.c 
ECHO  Output Files: libtcc.dll, libtcc.def
ECHO  Preprocessor Flags: -shared %Dflags% -DLIBTCC_AS_DLL 
%CC% -shared "..\libtcc.c" %Dflags% -DLIBTCC_AS_DLL -o "libtcc.dll" 
IF ERRORLEVEL 1 (
	ECHO [-] Unable To Compile: TCC Library: libtcc.dll
) ELSE ECHO [+] TCC Library is Compiled Successfuly.
ECHO.
ECHO Now we need -DONE_SOURCE"=0" option to test what it does.
ECHO I think that it is simply make libtcc.dll library usable with multiple architectures 
ECHO (With both TCC.exe x32 and x64)
pause