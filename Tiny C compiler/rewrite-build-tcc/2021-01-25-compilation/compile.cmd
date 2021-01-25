@ECHO OFF

REM [Checks if Processor architecture is X64]
REM This is valid method for both: Intel Processors and AMD Processors.
REM Most (if not all) Intel Processors are based on the same AMD64 instruction set.

REM PROCESSOR_ARCHITEW6432 is outdated Environment variable.
REM But it is still useful: to gather architecture from older Windows Operating systems.

IF "%PROCESSOR_ARCHITEW6432%" == "AMD64" SET "PROCESSOR_ARCHITECTURE=AMD64"
IF "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
	REM Preprocessor Options
	SET "NameMain=x86_64-win32"
	SET "D_optionsMain=-DTCC_TARGET_PE -DTCC_TARGET_X86_64"
	
	SET "NameSide=i386-win32"
	SET "optionsSide=-DTCC_TARGET_PE -DTCC_TARGET_I386"
	
	ECHO Yes
) 

REM Windows 2000
REM IF "%PROCESSOR_ARCHITECTURE%" == "x86" (
REM 	ECHO Second
REM )


pause