@ECHO OFF

:cl
@echo off
set CMD=cl
:c0
set ARG=%1
set ARG=%ARG:.dll=.lib%
if (%1)==(-shared) set ARG=-LD
if (%1)==(-o) shift && set ARG=-Fe%2
set CMD=%CMD% %ARG%
shift
if not (%1)==() goto :c0
echo on
%CMD% -O1 -W2 -Zi -MT -GS- -nologo -link -opt:ref,icf
@exit /B %ERRORLEVEL%

@rem ------------------------------------------------------
@rem main program

:p1

:Determine_Processor
IF DEFINED "tcc_cpu_architecture" GOTO :Compilation_Settings
SET "tcc_cpu_architecture=32"
IF "%PROCESSOR_ARCHITECTURE%"=="AMD64" SET "tcc_cpu_architecture=64"
IF "%PROCESSOR_ARCHITEW6432%"=="AMD64" SET "tcc_cpu_architecture=64"

:Compilation_Settings

SET CC=gcc
REM             https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
REM -s          Remove all symbol table and relocation information from the executable.
REM -static     Prevents linking with the shared libraries
REM             https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
REM -Os         Optimize for size. -Os enables all -O2 optimizations except those that often increase code size
IF "%CC%"=="gcc" SET "CC=%CC% -Os -s -static"

:p3
@echo on

:config.h
echo>..\config.h #define TCC_VERSION "%VERSION%"
echo>> ..\config.h #ifdef TCC_TARGET_X86_64
echo>> ..\config.h #define TCC_LIBTCC1 "libtcc1-64.a"
echo>> ..\config.h #else
echo>> ..\config.h #define TCC_LIBTCC1 "libtcc1-32.a"
echo>> ..\config.h #endif

for %%f in (*tcc.exe *tcc.dll) do @del %%f

:compiler
%CC% -o libtcc.dll -shared ..\libtcc.c %D% -DLIBTCC_AS_DLL
@if errorlevel 1 goto :the_end
%CC% -o tcc.exe ..\tcc.c libtcc.dll %D% -DONE_SOURCE"=0"

IF "%tcc_cpu_architecture%"=="32" %CC% -o x86_64-win32-tcc.exe ..\tcc.c -DTCC_TARGET_PE -DTCC_TARGET_I386
IF "%tcc_cpu_architecture%"=="64" %CC% -o i386-win32-tcc.exe ..\tcc.c -DTCC_TARGET_PE -DTCC_TARGET_X86_64

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
.\tcc -m%tcc_cpu_architecture% -c ../lib/bcheck.c -o lib/bcheck.o -g
.\tcc -m%tcc_cpu_architecture% -c ../lib/bt-exe.c -o lib/bt-exe.o
.\tcc -m%tcc_cpu_architecture% -c ../lib/bt-log.c -o lib/bt-log.o
.\tcc -m%tcc_cpu_architecture% -c ../lib/bt-dll.c -o lib/bt-dll.o

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
