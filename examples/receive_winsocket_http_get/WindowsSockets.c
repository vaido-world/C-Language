#pragma comment(lib,"ws2_32") //Winsock Library
#include<stdio.h>
#include<winsock2.h>

int main(int argc , char *argv[])
{

Initialization:
	printf("Initialising Winsock...");
	// http://etutorials.org/Programming/Pocket+pc+network+programming/Chapter+1.+Winsock/Winsock+Basics/
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
	// https://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata
	
	WORD wVersionRequired = MAKEWORD(2,2);
	WSADATA WindowsSocketsApiData;
	
	if (WSAStartup(wVersionRequired, &WindowsSocketsApiData) != 0){
		
		printf("Failed. Error Code : %d\n",WSAGetLastError());
		return 1;
	}
	printf("Initialised.\n");
	
	SOCKET NetworkSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (NetworkSocket == INVALID_SOCKET){
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");
	
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr("216.58.209.14");
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );
	
	
	printf("Connecting to remote server...");
	if (connect(NetworkSocket , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	puts("Connected");
	
	
	char *message;
	char server_reply[2000];
		
	printf("Send HTTP GET Request \n");	
	message = "GET / HTTP/1.1\r\n\r\n";
	if( send(NetworkSocket , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	
	//Receive a reply from the server
	int recv_size = recv(NetworkSocket, server_reply , sizeof(server_reply), 0);
	if(recv_size == SOCKET_ERROR)
	{
		puts("recv failed");
	}
	
	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts("-----------------------------------------------------------------------");
	puts(server_reply);

	
	
}