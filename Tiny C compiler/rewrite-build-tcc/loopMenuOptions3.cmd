@ECHO OFF

REM Loop arguments
REM Double Dash -- is a command option

REM Previous option was -c, accept as argument of -c
 
FOR %%G IN (%*) DO ( 
	SET "argument=%%G"
	IF NOT "!argument:~0,1!"=="-" ECHO not argument
	IF "%argument%"=="-c" SET "compile=y"
	
	IF "%argument%"=="-c" SET "compile=y"
)

