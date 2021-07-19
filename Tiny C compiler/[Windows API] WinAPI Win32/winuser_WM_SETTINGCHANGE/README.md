### Uninstalling
To uninstall it is better to keep track of the PATH added in a TEMP folder.  
To unistall all tcc compilers from the path a search and replace method can be used,  
but it is more dangerous as it would remove all of TCC added to the PATH, and that could be unwanted behaviour.  
Which means that a recovery file for those paths should be created and stored in a .txt text file.  

### Immediate acess to TCC on Command Prompt
https://docs.microsoft.com/en-us/windows/deployment/usmt/usmt-recognized-environment-variables

`where *.*`  can be used to list available programs in the Command Prompt.

**Problem:** Command prompt does not fetch PATH variable on runtime.  
PATH variable is fetched only when Command Prompt is launching by design.  

**Update:** `USERPROFILE=C:\Users\user` is also available to the the Command Prompt.  
This is a perfect location for temporary immmediate initiation.  

**Update2:** .lnk files are not accepted by command prompt by default as executables.     
It's best to make batch file that would launch the needed program.   

**Update3:** `temporary_path_user_location_cleanup.cmd` To delete the temporary files, the startup batch script might be needed that deletes itself as well.   
`C:\Users\user\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup` 
A Task Scheduler can be used as well, but it is too complicated and not as simple.

**Resolution:** Before the PATH variable is updated, to make immediate access of tcc.exe to the current Command Prompt Windows:  
Shortcuts to the tcc.exe can be made in the `C:/Windows` or `C:/Windows/System32` folders.

### Old information

```
where "tcc -version"
IF ERRORLEVEL 0 (
ECHO tcc.exe is now available.
ECHO Tiny C Compiler installed successfully
)

Tiny C Compiler has been Appended to the PATH variable using Registry. 
(HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment Path) 


Environment Variables have been reloaded.

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
