@ECHO OFF
TITLE Compile Tiny C with itself AND run WinSocket example

ECHO Downloading "Old Precompiled Tiny C Compiler" in .zip archive format
curl -L "http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win32-bin.zip" -O

ECHO Extracting "Old Precompiled Tiny C Compiler" .zip Archive
tar xf "tcc-0.9.27-win32-bin.zip"

ECHO Setting "Old Precompiled Tiny C Compiler" to a PATH variable
SET "PATH=%CD%\tcc;%PATH%"

ECHO Downloading "Latest Tiny C Compiler Source Code"
curl "https://repo.or.cz/tinycc.git/snapshot/HEAD.tar.gz" -O

ECHO Extracting "Latest Tiny C Compiler Source Code" .tar.gz Archive
tar xf "HEAD.tar.gz"

ECHO Opening "Latest Tiny C Compiler Source Code" extraction directory
CD "tinycc-HEAD-*"

REM Patch in progress
REM SET /p "version="<"VERSION" 
REM SET version_without_dots=%VERSION:.=%
REM IF %version_without_dots% GEQ 0927 (
REM 
REM if not exist win32\libtcc mkdir win32\libtcc
REM if not exist win32\doc mkdir win32\doc
REM 
REM copy include\*.h win32\include
REM copy tcclib.h win32\include
REM copy libtcc.h win32\libtcc
REM copy tests\libtcc_test.c win32\examples
REM 
REM pause
REM )


ECHO Opening "win32" directory of "Latest Tiny C Compiler Source Code"
CD "win32"

ECHO Launching "Tiny C Compiler Building Script"
START /B "build-tcc.bat" build-tcc.bat -c tcc -t 32 -i "..\..\latest-built"
ECHO Tiny C Compiler Successfully Compiled from the latest Source Code.

ECHO Trying to Unstuck from weirdly written "Tiny C Compiler Building Script"
ping 127.0.0.1 -n 6 > nul

ECHO If you see this, this script is still going, that means this script is successfully Unstuck, else something might have gone wrong

ECHO Opening the Directory of the "latest compiled Tiny C Compiler"
cd "..\..\latest-built"

ECHO Downloading "Source code for Winsocket test program"
curl "https://raw.githubusercontent.com/vaido-world/C-Language-Tutorial/master/Tiny%%20C%%20compiler/winsocketsResearch/WinSocktest.c" -O

ECHO Compiling "Source code for Winsocket test program"
tcc "WinSocktest.c" -lws2_32

ECHO Launching the compiled Winsocket Test Program.
WinSocktest.exe

ECHO ---------Diagnostics-----------

IF NOT EXIST "../win32/include/tccdefs.h" ( 
  IF EXIST "../include/tccdefs.h" ECHO ../include/tccdefs.h yes exist 
=	ECHO BUG DETECTED, x86_64-win32-tcc.exe will not be compiled.
	ECHO New evidence suggests: "tinycc-HEAD-704c816/include" is simply not copied to the "tinycc-HEAD-704c816/win32/include"
	ECHO  Explanation: "copy^>nul ..\include\*.h include" does not complete copy before execution of statement: "%%CC%% -o %%PX%%-tcc.exe ..\tcc.c %%DX%%"
	ECHO simply needs copy of files from tinycc-HEAD-704c816\include\.h to tinycc-HEAD-704c816\win32\include\.h manually
	ECHO Needs a bugfix inside in the build-tcc.bat
	ECHO The specific file that is missing: ^<command line^>:9: error: include file 'tccdefs.h' not found

)
ECHO -------------------------------

pause
ECHO The reason why this Command Line Window is not closing, is that build-tcc.bat has EXIT statement with /B option. 
ECHO Therefore build-tcc.bat Command Prompt Window is never closing. That's a bug of build-tcc, /B option should be removed everywhere.
ECHO x32recompiletcc.cmd launches build-tcc.bat without /WAIT option in the START statement, therefore x32recompiletcc.cmd does not wait until "build-tcc.bat" completes, but rahter when the same cpu thread is awailable?
ECHO After removing /B options from the EXIT statements in the build-tcc.bat /WAIT should be added and work properly in the x32recompiletcc.cmd

REM taskkill /F /FI "WindowTitle eq  build-tcc.bat" /T
REM little hack to prevent this script from being stuck after build-tcc.bat Exit 
