@REM Tiny C Compiler Build Script
@REM Supports: Windows 2000 and later

@ECHO OFF
@SETLOCAL EnableDelayedExpansion

REM Looping command-line arguments
REM 1. Checking if the first letter contains (-) hyphen character
REM 2. IF hyphen character is found
FOR %%G IN (%*) DO ( 
	SET "argument=%%G" 
	IF "!argument:~0,1!"=="-" (
		IF "!argument!"=="-c"(
			SET "compiling=y"
		)
		IF ""==""(
		
		)
		
	) ELSE (
	
	)
)