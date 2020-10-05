@ECHO OFF
ECHO Welcome to build-tcc.bat, the TCC building script

REM TCC Source Code Version
REM Getting TCC Source Code version from a File Named: VERSION
IF EXIST "..\VERSION" (
	SET /p "VERSION=" < "..\VERSION"
	CALL ECHO TCC Source Code has been detected of version: %%VERSION%%
	
) ELSE (
	ECHO Source Code Version file Error:
	ECHO Version file was not found in a path that is: ..\VERSION
	ECHO it is expected that outside the folder /win32/ there should be a Source Code Version file.
	EXIT /B 1
)


REM Default options reset
set CC=gcc
set INST=
set BIN=
set DOC=no
set EXES_ONLY=no

REM ----------------------Choice-and-Usage-Menu-------------------------------------

REM Options Input
IF ("%1")==("-i") SET INST=%2
IF ("%1")==("")   GOTO :usage 
IF ("%1")==("-c") GOTO :compilation 



REM The Usage Menu
:usage
echo usage: build-tcc.bat [ options ... ]
echo options:
echo   -c prog              use prog (gcc/tcc/cl) to compile tcc
echo   -c "prog options"    use prog with options to compile tcc
echo   -t 32/64             FORce 32/64 bit default target
echo   -v "version"         set tcc version
echo   -i tccdir            install tcc into tccdir
echo   -b bindir            optionally install binaries into bindir elsewhere
echo   -d                   create tcc-doc.html too (needs makeinfo)
echo   -x                   just create the executables
echo   -clean               delete all previously produced files and directories
EXIT /B 1



REM ----------------------Cleanup and the main program------------------------------
:cleanup
ECHO Removing files:

FOR %%F IN (*tcc.exe libtcc.dll lib\*.a) DO DEL %%F && ECHO %%F
FOR %%F IN (..\config.h ..\config.texi) DO DEL %%F && ECHO %%F
FOR %%F IN (include\*.h) DO IF EXIST ..\%%F DEL %%F && ECHO %%F
FOR %%F IN (include\tcclib.h examples\libtcc_test.c) DO DEL %%F && ECHO %%F
FOR %%F IN (lib\*.o *.o *.obj *.def *.pdb *.lib *.exp *.ilk) DO DEL %%F && ECHO %%F

ECHO Removing directories:
FOR %%F IN (doc libtcc) DO RMDIR /Q/S %%F && ECHO %%F
EXIT /B 0


:compilation
ECHO TCC Compilation Here

REM Gathering Processor Architecture
REM Checking if the -t option is set or not
REM option -t: Force 32/64 bit default target
IF NOT "%T%_"=="_" goto :checkCompiler

SET T=32
IF %PROCESSOR_ARCHITECTURE%_==AMD64_ SET T=64
IF %PROCESSOR_ARCHITEW6432%_==AMD64_ SET T=64


:CheckCompiler
REM Checks if selected compiler is GCC
REM sets some options for GCC compiler
IF "%CC:~-3%"=="gcc" SET CC=%CC% -Os -s -static
SET D32=-DTCC_TARGET_PE -DTCC_TARGET_I386
SET D64=-DTCC_TARGET_PE -DTCC_TARGET_X86_64
SET P32=i386-win32
SET P64=x86_64-win32
IF %T%==64 GOTO :t64
SET D=%D32%
SET DX=%D64%
SET PX=%P64%
:t64
set D=%D64%
set DX=%D32%
set PX=%P32%

REM Add configurations to the ..\config.h file
:config.h
ECHO>..\config.h #define TCC_VERSION "%VERSION%"
ECHO>> ..\config.h #ifdef TCC_TARGET_X86_64
ECHO>> ..\config.h #define TCC_LIBTCC1 "libtcc1-64.a"
ECHO>> ..\config.h #else
ECHO>> ..\config.h #define TCC_LIBTCC1 "libtcc1-32.a"
ECHO>> ..\config.h #endif

REM Deletes tcc.exe
FOR %%F IN (*tcc.exe *tcc.dll) DO DEL %%F



REM Compilation Begins


:compiler
%CC% -o libtcc.dll -shared ..\libtcc.c %D% -DLIBTCC_AS_DLL
@if errorlevel 1 goto :the_end
%CC% -o tcc.exe ..\tcc.c libtcc.dll %D% -DONE_SOURCE"=0"
%CC% -o %PX%-tcc.exe ..\tcc.c %DX%

@if (%EXES_ONLY%)==(yes) goto :files-done

if not exist libtcc mkdir libtcc
if not exist doc mkdir doc
copy>nul ..\include\*.h include
copy>nul ..\tcclib.h include
copy>nul ..\libtcc.h libtcc
copy>nul ..\tests\libtcc_test.c examples
copy>nul tcc-win32.txt doc

.\tcc -impdef libtcc.dll -o libtcc\libtcc.def
@if errorlevel 1 goto :the_end

:libtcc1.a
@set O1=libtcc1.o crt1.o crt1w.o wincrt1.o wincrt1w.o dllcrt1.o dllmain.o chkstk.o
.\tcc -m32 -c ../lib/libtcc1.c
.\tcc -m32 -c lib/crt1.c
.\tcc -m32 -c lib/crt1w.c
.\tcc -m32 -c lib/wincrt1.c
.\tcc -m32 -c lib/wincrt1w.c
.\tcc -m32 -c lib/dllcrt1.c
.\tcc -m32 -c lib/dllmain.c
.\tcc -m32 -c lib/chkstk.S
.\tcc -m32 -c ../lib/alloca86.S
.\tcc -m32 -c ../lib/alloca86-bt.S
.\tcc -m32 -ar lib/libtcc1-32.a %O1% alloca86.o alloca86-bt.o
@if errorlevel 1 goto :the_end
.\tcc -m64 -c ../lib/libtcc1.c
.\tcc -m64 -c lib/crt1.c
.\tcc -m64 -c lib/crt1w.c
.\tcc -m64 -c lib/wincrt1.c
.\tcc -m64 -c lib/wincrt1w.c
.\tcc -m64 -c lib/dllcrt1.c
.\tcc -m64 -c lib/dllmain.c
.\tcc -m64 -c lib/chkstk.S
.\tcc -m64 -c ../lib/alloca86_64.S
.\tcc -m64 -c ../lib/alloca86_64-bt.S
.\tcc -m64 -ar lib/libtcc1-64.a %O1% alloca86_64.o alloca86_64-bt.o
@if errorlevel 1 goto :the_end
.\tcc -m%T% -c ../lib/bcheck.c -o lib/bcheck.o -g
.\tcc -m%T% -c ../lib/bt-exe.c -o lib/bt-exe.o
.\tcc -m%T% -c ../lib/bt-log.c -o lib/bt-log.o
.\tcc -m%T% -c ../lib/bt-dll.c -o lib/bt-dll.o

:tcc-doc.html
@if not (%DOC%)==(yes) goto :doc-done
echo>..\config.texi @set VERSION %VERSION%
cmd /c makeinfo --html --no-split ../tcc-doc.texi -o doc/tcc-doc.html
:doc-done

:files-done
for %%f in (*.o *.def) do @del %%f

:copy-install
@if (%INST%)==() goto :the_end
if not exist %INST% mkdir %INST%
@if (%BIN%)==() set BIN=%INST%
if not exist %BIN% mkdir %BIN%
for %%f in (*tcc.exe *tcc.dll) do @copy>nul %%f %BIN%\%%f
@if not exist %INST%\lib mkdir %INST%\lib
for %%f in (lib\*.a lib\*.o lib\*.def) do @copy>nul %%f %INST%\%%f
for %%f in (include examples libtcc doc) do @xcopy>nul /s/i/q/y %%f %INST%\%%f

:the_end
exit /B %ERRORLEVEL%

