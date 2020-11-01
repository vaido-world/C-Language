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
 
 
 
 ## Changing Environment variables of child processes are not recommended
 https://stackoverflow.com/questions/3636055/how-to-modify-the-path-variable-definitely-through-the-command-line-in-windows/3637478#3637478  
 https://docs.microsoft.com/lt-lt/windows/win32/procthread/changing-environment-variables?redirectedfrom=MSDN  


## Alternative Implementation in D language 
https://forum.dlang.org/post/ngkhsaadchcqbdvmorot@forum.dlang.org
