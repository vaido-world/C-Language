```
TCC compiler is now available for the new Command Prompt processes!
Type tcc --version
```
Reloads Windows Environment variables for new processes.

* Works the same as the Official Windows "Edit the system environment variables" GUI.
* Command Prompts that are already opened will not be affected. (Same as using "Edit the system environment variables" GUI)
  * Therefore Active Command Prompts have to Set Environment variables themselves to get them reloaded.
   ```
   for /f "tokens=2*" %%A in ('REG QUERY "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path ^|FIND /I "Path"') DO (
  SET path=%%B
  )
   
   ```
 
 Refrences:
 https://stackoverflow.com/questions/3636055/how-to-modify-the-path-variable-definitely-through-the-command-line-in-windows/3637349#3637349
 
 ## Windows Console Host `C:\Windows\System32\conhost.exe` might be interesting thing to look at
 > The Windows Console Host, or conhost.exe, is both the server application for all of the Windows Console APIs as well as the classic Windows user interface for working with command-line applications.https://docs.microsoft.com/en-us/windows/console/definitions#console-host
 Source code can be found here: https://github.com/microsoft/terminal/tree/ae550e0969595f062b15c2ff5cc33d4afe8ebc3f/src/host/exe
 
 ## Changing Environment variables of child processes are not recommended
 https://stackoverflow.com/questions/3636055/how-to-modify-the-path-variable-definitely-through-the-command-line-in-windows/3637478#3637478  
 https://docs.microsoft.com/lt-lt/windows/win32/procthread/changing-environment-variables?redirectedfrom=MSDN  


## Alternative Implementation in D language 
https://forum.dlang.org/post/ngkhsaadchcqbdvmorot@forum.dlang.org
