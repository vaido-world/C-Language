@REM  ------------------------------------------------------
@REM build-tcc.bat 
@REM Batch file to build tcc using mingw, msvc or tcc itself
@REM  ------------------------------------------------------
@ECHO OFF
REM ------------------------Default-Compiler--------------------------------------

REM Blocks from opening in non interactive
REM IF NOT "%0"=="%~dp0\build-tcc.cmd" ECHO Interactive
IF NOT "%~0"=="%~f0" ECHO Interactive
pause

IF "%1"=="" (
	WHERE "gcc.exe" >NUL 2>NUL
	REM compares multiple error levels: 0 - Successfull Where, 1 - Whether the gcc was not found
	IF NOT ERRORLEVEL 01 (
		ECHO              DEFAULT COMPILER will be used
		ECHO          GCC is the suggested default compiler
		ECHO __________________________________________________________
		GOTO :usingGCC
	)
)

REM ---------------------Command-Line-Interface-----------------------------------
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

REM -------------------Command-Line-Interface-Loop---------------------------------


REM DEFAUTLS For Options
SET "Architecture=%PROCESSOR_ARCHITECTURE%%PROCESSOR_ARCHITEW6432%"
IF NOT "%Architecture%"=="AMD64" SET "Architecture=x32"

WHERE "tcc.exe" >NUL 2>NUL && IF ERRORLEVEL 0 SET "CC=tcc"
WHERE "cl.exe"  >NUL 2>NUL && IF ERRORLEVEL 0 SET "CC=cl"
WHERE "gcc.exe" >NUL 2>NUL && IF ERRORLEVEL 0 SET "CC=gcc"
REM TODO CALL :SearchAroundForCompiler
IF "CC"="" ECHO NO COMPILERS FOUND && EXIT /B 1
SET /p Version= < "..\VERSION"
SET "Installation_folder=%~DP0"
SET "Binaries_location=%~DP0"
SET "Documentation=yes"
SET "EXES_ONLY=no"

REM Main Options LOOP
:OptionsLoop
IF "%1"=="-c" ( 
	SET "CC=%~2"
	IF "%2"=="cl" SET "CC=@CALL :cl"
	SHIFT
	SHIFT
	GOTO :OptionsLoop
)

IF (%1)==(-t) SET "Architecture=%2"          && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-v) SET "Version=%~2"              && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-i) SET "Installation_folder=%2"   && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-b) SET "Binaries_location=%2"     && SHIFT && SHIFT && GOTO :OptionsLoop
IF (%1)==(-d) SET "Documentation=yes"        && SHIFT && GOTO :OptionsLoop
IF (%1)==(-x) SET "EXES_ONLY=yes"            && SHIFT && GOTO :OptionsLoop
ECHO _______________________________________

REM TODO CHECK IF CMD STARTED IN INTERACTIVE MODE
ECHO Selected_Source_compiler: %CC%
ECHO Host_compiler: %CC%
ECHO Builder: %CC%
ECHO Architecture: %Architecture%
ECHO Version: %Version%
ECHO Installation_folder: %Installation_folder%
ECHO Binaries_location: %Binaries_location%
ECHO Documentation: %Documentation%
ECHO Only Executables: %EXES_ONLY%
ECHO _______________________________________
IF (%1)==() GOTO :processFlags


:usingGCC
REM ------------------------GCC-Compiler--------------------------------------
gcc --version
ECHO GCC Compilation


