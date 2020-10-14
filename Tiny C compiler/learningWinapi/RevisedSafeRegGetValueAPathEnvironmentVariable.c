#pragma comment(lib, "advapi32") // No more Need for tcc -ladvapi32 RegGetValueA.c         tcc: error: undefined symbol 'RegGetValueA' 
#include <stdio.h>               // Prevents a warning:                  test.c:34: warning: implicit declaration of function 'printf'
#include <windows.h>             // Required, else an error:             test.c:12: error: 'DWORD' undeclared
#include <stdlib.h>              // Gives access to Malloc, Calloc, Realloc


void main(){

	#define BUFFER  8192
	DWORD BufferSize = BUFFER;
	
	HKEY    hkey     = HKEY_LOCAL_MACHINE;
	LPCSTR  lpSubKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";
	LPCSTR  lpValue  = "Path";
	DWORD   dwFlags  = RRF_RT_ANY;
	LPDWORD pdwType  = NULL;
	PVOID   pvData   = NULL;
	LPDWORD pcbData  = &BufferSize;
	
	RegGetValueA(
		hkey,
		lpSubKey,
		lpValue,
		dwFlags,
		pdwType,
		pvData,
		pcbData
	);

	pvData = (int*)malloc(*pcbData);
	
	RegGetValueA(
		hkey,
		lpSubKey,
		lpValue,
		dwFlags,
		pdwType,
		pvData,
		pcbData
	);
	
		printf("                  ---");
		printf("\n");
		printf("%s", pvData);
		printf("\n");
		printf("                  ---");
		printf("\n");
		printf("\nRetrieved information about array size: %i\n",*pcbData);
		printf("Actual size of the array: %i\n", strlen(pvData));
		printf("Manually Allocated bytes for the array: %zu", sizeof(pvData));
		printf("\nSince malloc was used, the dynamic Allocation makes the Manual Allocation results strange.");
		// https://stackoverflow.com/questions/37447198/dynamically-allocated-variable-size
	
	
}
