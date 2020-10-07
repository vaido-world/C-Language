Check if command option is -clean, GOTO :cleanup, EXIT /B 0
SET gcc as default a compiler 
GET VERSION of the TCC Source File
Reset variables:
	set INST=
	set BIN=
	set DOC=no
	set EXES_ONLY=no
GOTO :a0
if command option is not -c , GOTO :a1
if command option is -c , Set compiler variable CC to the second argument.
if second argument is cl, Set compiler variable 
%~2
Expand %2 removing any surrounding quotes (")
https://github.com/vaido-world/C-Language-Tutorial/blob/master/Tiny%20C%20compiler/rewrite-build-tcc/original-build-tcc.bat#L28

