@ECHO OFF
:: This script is not working, just a test.
:: Script inspiration and Setup Reference: https://stackoverflow.com/a/9351171/3789797

:: export definitions from the DLL file using the command line:
tcc -impdef wsock32.dll -o .\lib\wsock32.def

:: Since latest Windows 10 release, curl is supported and can be used in Command Line.
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/winsock2.h -O
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/ws2tcpip.h -O
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/ws2spi.h -O
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/crt/_mingw_unicode.h -O
move *.h "include"

mkdir .\include\psdk_inc\
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/psdk_inc/_ws1_undef.h -o ./include/psdk_inc/_ws1_undef.h

curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/crt/_timeval.h -O
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/crt/_bsd_types.h -O
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/inaddr.h -O
move *.h "include"

mkdir .\include\psdk_inc\
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/psdk_inc/_socket_types.h -o ./include/psdk_inc/_socket_types.h
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/psdk_inc/_fd_types.h -o ./include/psdk_inc/_fd_types.h
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/psdk_inc/_ip_types.h -o ./include/psdk_inc/_ip_types.h
curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/psdk_inc/_wsadata.h -o ./include/psdk_inc/_wsadata.h

curl https://raw.githubusercontent.com/mirror/mingw-w64/master/mingw-w64-headers/include/ws2def.h -O
move *.h "include"



:: At compilation time, you will need to tell the compiler you are using the Windows socket library:
:: tcc.exe path\to\code.c -lwsock32 -o path\to\program.exe

:: winsock-example http://www.rohitab.com/discuss/topic/28719-downloading-a-file-winsock-http-c/
tcc.exe winsock-example.c -lwsock32 -o winsock-example.exe


:: tcc  winsock-example.c  winsock.def -o  winsock-example.exe
pause


:: Shorter version for gathering headers from Mingw project

curl -L https://github.com/mirror/mingw-w64/archive/master.zip -O

tar xvfz master.zip mingw-w64-master/mingw-w64-headers/include
tar xvfz master.zip mingw-w64-master/mingw-w64-headers/crt

move .\mingw-w64-master\mingw-w64-headers\include\* .\include 
move .\mingw-w64-master\mingw-w64-headers\crt\* .\include 