#include <stdio.h>
#include <windows.h>

void main(){

	DWORD nBufferLength;
	nBufferLength = GetCurrentDirectory(
	  0,
	  NULL
	);

	LPTSTR lpBuffer[nBufferLength];

	GetCurrentDirectory(
	  nBufferLength,
	  (LPTSTR)lpBuffer
	);




	printf("Bytes: %i", nBufferLength);
	printf("\n");
	printf("%s", lpBuffer);
	printf("\\");
	printf(__FILE__);

}
