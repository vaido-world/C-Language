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

 

