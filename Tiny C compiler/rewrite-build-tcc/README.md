Stuck with 
Looping through menu options seems to be harder than I though.


**original-build-tcc.bat** can be deleted, it is original from the **/win32/build-tcc.bat** folder  
However, has some lines seperation for more visual cues on how the script works.  

**VERSION** file can be deleted as well, it was used for testing TCC Source Code Version verification. Now it works, can be deleted.  
The Version file can be found in **../VERSION**

This is the core rewrite that is not complete: **/win32/build-tcc-rewrite.cmd**  
As mentioned, stuck with **loopMenuOptions.cmd**  


All this has been started since there is a bug with the **build-tcc.bat**   
that requires two pass compilation, when it should be a single pass - when using/calling from other scripts.
Sometimes TCC build script simply does not produce all the files.
