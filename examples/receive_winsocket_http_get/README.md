Always remember to make a definition file (.def) from the library file (.dll) `tcc -impdef ws2_32.dll -o .\lib\ws2_32.def`  
Also remember to change to a different ip, since right now it is google.com ip which is known to be dynamic/changing over time.  
This code is from https://www.binarytides.com/winsock-socket-programming-tutorial/  


## Receiving full data without knowing the end file size
https://www.binarytides.com/receive-full-data-with-recv-socket-function-in-c/

## Connecting to a socket via domain name instead of ip
https://docs.microsoft.com/lt-lt/windows/win32/api/wsipv6ok/nf-wsipv6ok-gethostbyname?redirectedfrom=MSDN

```
C:\Users\Vaidas\Desktop>tcc -run receive.c google.com
Calling gethostbyname with google.com
Function returned:
        Official name: google.com
        Address type: AF_INET
        Address length: 4
        IP Address #1: 216.58.209.14
```
