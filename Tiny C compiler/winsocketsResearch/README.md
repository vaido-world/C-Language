I'm unable to make winsockets to work.  
These are only trials that do not work.  




## About the Win32 API - platform
https://docs.microsoft.com/en-us/windows/win32/desktop-programming

# Winsock

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
> The Ws2_32.dll loads the service provider's interface DLL into the system by using the standard Microsoft Windows dynamic library loading mechanisms, and initializes it by calling WSPStartup. This is typically triggered by an application calling either socket or WSASocket to create a new socket to be associated with a service provider whose interface DLL is not currently loaded into memory. The path to each service provider's interface DLL is stored by the Ws2_32.dll at the time the service provider is being installed. See Installation and Configuration Functions for more information.
https://docs.microsoft.com/en-us/windows/win32/winsock/initialization-2


