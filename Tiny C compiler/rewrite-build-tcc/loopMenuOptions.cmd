@ECHO OFF

REM Delayed expansion workaround notice https://stackoverflow.com/a/44963641/3789797
REM parameter
FOR %%G IN (%*) DO ( 
	SET "commandLineArgument=%%G"
	CALL SET "commandLineArgument=%%commandLineArgument%%"
	REM echo %commandLineArgument:~0,1% dddddddddd
	call echo %%commandLineArgument:~0,1%% -here
	IF "%commandLineArgument:~0,1%"=="5" (
		ECHO IS an argument
	)
		
	
	IF "%%G"=="-c" ( 
		REM ECHO A Compilation, found -c flag
		SET "cArgument="
		SET "checkForArgument=yes"
	)

)





exit /B 0
set "name=-vaid"
echo %name:~0,1%
