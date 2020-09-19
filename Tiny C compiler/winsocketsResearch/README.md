I'm unable to make winsockets to work.  
These are only trials that do not work.  




## About the Win32 API - platform
https://docs.microsoft.com/en-us/windows/win32/desktop-programming

# About Winsock
https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2

https://docs.microsoft.com/en-us/windows/win32/winsock/creating-a-basic-winsock-application

ws2_32.def  
can be found in https://github.com/TinyCC/tinycc/tree/mob/win32/lib



## Generating .def file of ws2_32.dll
```
tcc -impdef ws2_32.dll
```


## Winsock Distribution

#### previous research
ws2_32.dll is **probably** distributed via  vc_redist.x64.exe and vc_redist.x86.exe
https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads
#### latest research
https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
> The Winsock2.h header file for Winsock 2 support is included with the Microsoft Windows Software Development Kit (SDK).

#### ws2tcpip.h
`C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um\ws2tcpip.h`
#### WinSock2.h
`C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um\WinSock2.h`


## Initialization of winsock
> **The Ws2_32.dll loads the service provider's interface DLL into the system by using the standard Microsoft Windows dynamic library loading mechanisms, and initializes it by calling WSPStartup.** This is typically triggered by an application calling either socket or WSASocket to create a new socket to be associated with a service provider whose interface DLL is not currently loaded into memory. **The path to each service provider's interface DLL is stored by the Ws2_32.dll** at the time the service provider is being installed. See Installation and Configuration Functions for more information.
https://docs.microsoft.com/en-us/windows/win32/winsock/initialization-2


## The default path to Microsoft Windows Software Development Kit (SDK)

``C:\Program Files (x86)\Windows Kits\10\``
## Estimated size of Microsoft Windows Software Development Kit (SDK)
> 2,6gb
