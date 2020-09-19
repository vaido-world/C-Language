I'm unable to make winsockets to work.  
These are only trials that do not work.  

https://docs.microsoft.com/en-us/windows/win32/winsock/creating-a-basic-winsock-application

ws2_32.def  
can be found in https://github.com/TinyCC/tinycc/tree/mob/win32/lib

ws2_32.dll is probably distributed via  vc_redist.x64.exe and vc_redist.x86.exe  
https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads



## Generating .def file of ws2_32.dll
```
tcc -impdef ws2_32.dll
```

## Initialization of winsock
https://docs.microsoft.com/en-us/windows/win32/winsock/initialization-2
