#pragma comment(lib, "advapi32") // No more Need for tcc -ladvapi32 RegGetValueA.c         tcc: error: undefined symbol 'RegGetValueA' 
#include <stdio.h>               // Prevents a warning:                  test.c:34: warning: implicit declaration of function 'printf'
#include <windows.h>             // Required, else an error:             test.c:12: error: 'DWORD' undeclared
/* 
Useful information 
   Function:  RegGetValueA
   Reference: https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-reggetvaluea
   
                                 //Required, else an error:               tcc: error: undefined symbol 'RegGetValueA'
 Proper compilation method/tutorial 
   tcc -impdef advapi32.dll -o .\lib\advapi32.def
   tcc -ladvapi32 RegGetValueAPathEnvironmentVariable.c

More Documentation
   System Path variable locations
   https://stackoverflow.com/questions/573817/where-are-environment-variables-stored-in-registry/573818#573818

   User Variables
   HKEY_CURRENT_USER\Environment

   System Variables
   Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment

*/



void main(){
	
	// Notice: the program silently crashes if there are not enough characters allocated
	// https://docs.microsoft.com/en-us/windows/win32/seccrypto/retrieving-data-of-unknown-length
	// https://stackoverflow.com/questions/9137157/no-out-of-bounds-error/9137188#9137188
	// Allocating 2048 bytes = 2kb for the Path variable output
	char value[2048];
	
	#define BUFFER  8192
	DWORD BufferSize = BUFFER;
	
	HKEY    hkey     = HKEY_LOCAL_MACHINE;
	LPCSTR  lpSubKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";
	LPCSTR  lpValue  = "Path";
	DWORD   dwFlags  = RRF_RT_ANY;
	LPDWORD pdwType  = NULL;
	PVOID   pvData   = &value;
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
	
	
	if (BufferSize >= strlen(value)) {
		printf("                  ---");
		printf("\n");
		printf("%s", value);
		printf("\n");
		printf("                  ---");
		printf("\n");

		printf("Retrieved information about array size: %i\n",BufferSize);
		printf("Actual size of the array: %i\n", strlen(value));
		printf("Manually Allocated bytes for the array: %i", sizeof(value));
	
	} else {
		
		// This is not going to be seen, 
		// the program crashes when the array is too small, therefore out of bounds
		// printf("Is too small");
	}
	
	// https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c
	// https://stackoverflow.com/questions/308695/how-do-i-concatenate-const-literal-strings-in-c/308712#308712

}
