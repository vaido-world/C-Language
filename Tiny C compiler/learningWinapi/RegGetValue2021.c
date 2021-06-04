#pragma comment(lib, "advapi32") // No more Need for "tcc -ladvapi32 RegGetValueA.c"         tcc: error: undefined symbol 'RegGetValueA' 

// Include directives.
#include <stdio.h>               // Prevents a warning:                  test.c:34: warning: implicit declaration of function 'printf'
#include <windows.h>             // Required, else an error:             test.c:12: error: 'DWORD' undeclared
#include <stdlib.h>              // Required, else a warning:            RegGetValue.c:62: warning: implicit declaration of function 'malloc'


// TODO:
// Use this as application for interfacing with PATH variables.
// Gather a folder using the function arguments.
// Simply append the folder at the end of the output.
// Check if the string already contains 
// if contains, use search and replace to replace the thing with empty
// https://github.com/vaido-world/C-Language-Tutorial/blob/master/FindAndReplaceString.c

// This source code is in Ansi mode.
void main(){
		printf(TEXT("_________________________________________ \n"));
		printf(TEXT("_______________RegGetValue_______________ \n"));
		// Types Definitions for RegGetValue function arguments
		HKEY    hkey;
		LPCSTR  lpSubKey;
		LPCSTR  lpValue;
		DWORD   dwFlags;
		LPDWORD pdwType; 
		PVOID   pvData; 
		LPDWORD pcbData;
					

		// Holds size of the buffer for pvData value in bytes
		DWORD BufferSize;
	
		// Error Codes Handling
		LONG error;
	
		// RegGetValue, Retrieves the type and data for the specified registry value. https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-reggetvaluea
		error = RegGetValueA(
			hkey     = HKEY_LOCAL_MACHINE,
			lpSubKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",
			lpValue  = "Path",
			dwFlags  = RRF_RT_ANY,
			pdwType  = NULL, // This default NULL value, states that we do not request specific registry value type  https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry-value-types
			pvData   = NULL, // This default NULL value, states that we do not request the data, only the Size of it
			pcbData  = &BufferSize
		);
		
		// For RegGetValueA only
		// RegGetValueW needs printfw
		printf(TEXT("Information \n"));
		if ( hkey == HKEY_LOCAL_MACHINE){ printf("  hkey: HKEY_LOCAL_MACHINE (value in Hexadecimal: 0x%x)\n", hkey); }
		if ( hkey == HKEY_CURRENT_USER ){ printf("  hkey: HKEY_CURRENT_USER  (value in Hexadecimal: 0x%x)\n", hkey); }
		if ( hkey == HKEY_USERS ){ printf("  hkey: HKEY_USERS   (value in Hexadecimal: 0x%x)\n", hkey); }
		printf(TEXT("  lpSubKey: %s \n"), lpSubKey);
		printf(TEXT("  lpValue: %s \n"), lpValue);
		
		if (error != ERROR_SUCCESS)
			{
				if (error == ERROR_FILE_NOT_FOUND){
					printf(TEXT("  ERROR on line %d: The '%s' subkey could not be opened. Error code: %x\n"), __LINE__, lpSubKey, error );
					
				} else {
					wprintf(L"Please consult the error https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-. Error code: %x\n", lpSubKey, error);
					
				}
			}
	
		// Allocate memory for the pvData in size of retrieved pcbData value
		pvData = (int*)malloc(*pcbData);

		error = RegGetValueA(
				hkey,
				lpSubKey,
				lpValue,
				dwFlags,
				pdwType,
				pvData,
				pcbData
			);

		if (error != ERROR_SUCCESS)
			{
				if (error == ERROR_FILE_NOT_FOUND){
					printf(TEXT("  ERROR on line %d: The '%s' subkey could not be opened. Error code: %x\n"), __LINE__, lpSubKey, error );
				} else {
					wprintf(L"Please consult the error https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-. Error code: %x\n", lpSubKey, error);
					
				}
			}

		printf("Output \n");
		printf("                  ----Output---");
		printf("\n");
		printf("%s", pvData);
		printf("\n");
		printf("                  ---");
		printf("-Debug---- \n");
		printf("\n");
		printf("\nRetrieved information about array size: %i bytes.\n",*pcbData);
		printf("Actual size of the array: %i characters counted.\n", strlen(pvData));
		printf("Manually Allocated bytes for the array: %zu bytes.", sizeof(pvData));
		printf("\nSince malloc was used, the dynamic Allocation makes the Manual Allocation results strange.");
}
