@ECHO OFF


REM start /MIN /B  "sdf" "tcc.exe" -run %~1
"tcc.exe" -Wlsubsystem=windows -run %~1
echo.


EXIT
@ECHO OFF
%windir%\system32\cmd.exe /c "tcc.exe -run %1"
echo.
REM pause