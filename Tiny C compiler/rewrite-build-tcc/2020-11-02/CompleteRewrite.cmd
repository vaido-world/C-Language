@rem ------------------------------------------------------
@rem batch file to build tcc using mingw, msvc or tcc itself
@rem ------------------------------------------------------
@ECHO OFF

REM tcc --version

:: The installers do not automatically modify any environment settings, (in particular the PATH).
:: You will need to add the MinGW `bin' directory, as described in the "Environment Settings" section below.
:: http://www.mingw.org/wiki/getting_started#Cautions
:: gcc


REM ---------------------Indication-and-information-------------------------------

IF EXIST "%systemdrive%\MinGW" ECHO [+] Default location of MinGW has been found.
IF EXIST "%systemdrive%\MinGW" ECHO     [+] Installation Location: %systemdrive%\MinGW
IF EXIST "%systemdrive%\MinGW\bin\gcc.exe" ECHO     [+] Hope of package installed: 
IF EXIST "%systemdrive%\MinGW\bin\gcc.exe" ECHO          [+] mingw32-base-bin ^| A Basic MinGW Installation

IF NOT EXIST "%systemdrive%\MinGW" CALL :determineMinGW 
IF NOT EXIST "%systemdrive%\MinGW" IF EXIST "%path_to_MinGWFolder%MinGW" ECHO [+] Guessed location of MinGW ^( %path_to_MinGWFolder%MinGW ^)
IF NOT EXIST "%systemdrive%\MinGW" (
	IF EXIST "%path_to_MinGWFolder%MinGW\bin\gcc.exe" (
		ECHO     [+] gcc found, determinations successful ^(%path_to_MinGWFolder%MinGW\bin\gcc.exe ^)
	)
)

WHERE "gcc.exe" > "%TEMP%/gcc-path.txt" 2>NUL && IF ERRORLEVEL 0 (
	ECHO [+] Detected GCC Compiler inside PATH Environment Variable
	SET /p gccPath=<%TEMP%\gcc-path.txt
	echo     [+] gcc.exe: %gccPath%
)

WHERE "tcc.exe" > "%TEMP%/tcc-path.txt" 2>NUL && IF ERRORLEVEL 0 (
	ECHO [+] Detected TCC Compiler inside PATH Environment Variable
	SET /p tccPath=<%TEMP%\tcc-path.txt
	echo     [+] tcc.exe: %tccPath%
)

WHERE "cl.exe" > "%TEMP%/cl-path.txt" 2>NUL && IF ERRORLEVEL 0 (
	ECHO [+] Detected MSVC Compiler inside PATH Environment Variable
	SET /p clPath=<%TEMP%\cl-path.txt
	echo     [+] cl.exe: %clPath%
)
ECHO __________________________________________________________

REM ------------------------Default-Compiler--------------------------------------

IF "%1"=="" (
	WHERE "gcc.exe" >NUL 2>NUL 
	IF ERRORLEVEL 0 (
		ECHO              DEFAULT COMPILER will be used
		ECHO          GCC is the suggested default compiler
		ECHO __________________________________________________________
		gcc --version
		goto :usingGCC
	)
)


REM ---------------------Command-Line-Interface-----------------------------------
pause
exit /B 1
IF (%1)==() (

	ECHO usage: build-tcc.bat [ options ... ]
	ECHO options:
	ECHO   -c prog              use prog ^(gcc/tcc/cl^) to compile tcc
	ECHO   -c "prog options"    use prog with options to compile tcc
	ECHO   -t 32/64             force 32/64 bit default target
	ECHO   -v "version"         SET tcc version
	ECHO   -i tccdir            install tcc into tccdir
	ECHO   -b bindir            optionally install binaries into bindir elsewhere
	ECHO   -d                   create tcc-doc.html too ^(needs makeinfo^)
	ECHO   -x                   just create the executables
	ECHO   -clean               delete all previously produced files and directories
	EXIT /B 1

)

:OptionsLoop
IF "%1"=="-c" ( 
	SET "CC=%~2"
	IF "%2"=="cl" SET "CC=@CALL :cl"
	SHIFT
	SHIFT
	GOTO :OptionsLoop
)
IF (%1)==(-t) SET "T=%2"          && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-v) SET "VERSION=%~2"   && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-i) SET "INST=%2"       && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-b) SET "BIN=%2"        && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-d) SET "DOC=yes"       && SHIFT && GOTO :OptionsLoop
IF (%1)==(-x) SET "EXES_ONLY=yes" && SHIFT && GOTO :OptionsLoop
IF (%1)==() GOTO :p1


:usingGCC
REM ------------------------GCC-Compiler--------------------------------------
ECHO GCC Compilation

pause



EXIT
:determineMinGW
REM determineMinGW.cmd
REM Try to determine MinGW installation location 
REM by looking at a list of previously used .exe programs by the current computer user
FOR /F "tokens=1 usebackq" %%A ^
IN (`reg query "HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Compatibility Assistant\Store" /S ^| FIND "MinGW"`) ^
DO (
	REM IF NOT "%%A"=="" ECHO MINGW found, determined from %%A 
	SET "MinGW_paths=%%A"
)
	set path_to_MinGWFolder=%MinGW_paths:MinGW\=&rem;%
	REM echo %path_to_MinGWFolder%MinGW
GOTO :EOF
	
	
	pause
	
