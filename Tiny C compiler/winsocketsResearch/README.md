
## 2020-09-21 Update: 
I was abled to finally use winsocket in a program.  
Simply you just have to compile the latest TCC compiler.

The precompiled compilers on http://download.savannah.gnu.org/releases/tinycc/  
Did not work, they are outdated.

Here is a tutorial for compiling Tiny C Compiler:  
https://github.com/vaido-world/C-Language-Tutorial/tree/master/Tiny%20C%20compiler/compilingTCC

After compilation simply use the newly compiled latest TCC
and test if Winsockets works for you:


Compile the below example this way: `tcc WinSocktest.c -lws2_32`  
The output should look like this:
```
C:\Users\boqsc\Desktop\built>WinSocktest.exe
socket id: 172
```

### WinSocktest.c
```
#include <stdio.h>

#include <winsock2.h>

 

int

main() {

    WSADATA wsaData;

    SOCKET so;

    (void)WSAStartup(MAKEWORD(2,2), &wsaData);

    so = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP);

    printf("socket id: %d\n", so);

    closesocket(so);

    WSACleanup();   

}

 

C:>tcc foo.c -lws2_32 && foo

Socket id: 180
```

----
# ~~Older research, not relevant anymore~~


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

## Linking header files from Microsoft Windows Software Development Kit (SDK)
> Preprocessor options:
>   -Idir       add include path 'dir'


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


# Tests
```
C:\Users\Juozas\Desktop\3tcc>tcc baisc.c "-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um"
In file included from baisc.c:1:
C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/winsock2.h:20: error: include file 'winapifamily.h' not found

C:\Users\Juozas\Desktop\3tcc>tcc baisc.c "-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um"tcc baisc.c "-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um" "-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\shared"

C:\Users\Juozas\Desktop\3tcc>tcc baisc.c "-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um" "-IC:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\shared"
In file included from baisc.c:1:
In file included from C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/winsock2.h:53:
In file included from C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/windows.h:167:
In file included from c:/users/juozas/desktop/3tcc/include/excpt.h:9:
c:/users/juozas/desktop/3tcc/include/_mingw.h:167: warning: WINAPI_FAMILY_PARTITION redefined
In file included from baisc.c:1:
In file included from C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/winsock2.h:53:
In file included from C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/windows.h:171:
In file included from C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/shared/windef.h:24:
In file included from C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/shared/minwindef.h:182:
C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um/winnt.h:3042: error: ';' expected (got "LONG")

C:\Users\Juozas\Desktop\3tcc>
```
