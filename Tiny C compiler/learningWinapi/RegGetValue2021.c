#pragma comment(lib, "advapi32") // No more Need for "tcc -ladvapi32 RegGetValueA.c"         tcc: error: undefined symbol 'RegGetValueA' 

// Include directives.
#include <stdio.h>               // Prevents a warning:                  test.c:34: warning: implicit declaration of function 'printf'
#include <windows.h>             // Required, else an error:             test.c:12: error: 'DWORD' undeclared
#include <stdlib.h>              // Required, else a warning:            RegGetValue.c:62: warning: implicit declaration of function 'malloc'

// Redefine Main method


//#ifndef RegGetPathValue_C
//#define RegGetPathValue_C
//#include "RegGetPathValue.c"
//#endif

// #ifndef main
// #define main main
// #define openRegistryKey main
// #endif
// 
// #ifndef NEWONE_C
// #define NEWONE_C
// #include "newone.c"
// #endif


void openRegistryKey();
void getRegistryKeyValue();

    // For hKey argument
	// Makes Accept both hex values, integer values and string values
	// HKEY_LOCAL_MACHINE       80000002      0x80000002
void main(){

	
	openRegistryKey();
	
}


void openRegistryKey(
	HKEY   hKey,
	LPCSTR lpSubKey,
	DWORD  ulOptions,
	REGSAM samDesired,
	PHKEY  phkResult){
	  
	HKEY subKey;
	  
	LONG error = RegOpenKeyExA(
		hKey      = HKEY_CURRENT_CONFIG,
		lpSubKey  = "",	  
		ulOptions = 0,
		samDesired = KEY_READ,
		phkResult = &subKey
	);
	
	if (error == ERROR_SUCCESS) {
		printf("The registry key has been opened successfully\n");
				
		switch ((int) hKey){
			case HKEY_CLASSES_ROOT:
				
				printf("It's HKEY_CLASSES_ROOT, 0x%x \n", hKey);
				break;
				
			case HKEY_CURRENT_USER:
				printf("It's HKEY_CURRENT_USER, 0x%x \n", hKey);
				break;
				
			case HKEY_LOCAL_MACHINE:
				printf("It's HKEY_LOCAL_MACHINE, 0x%x \n", hKey);
				break;
				
			case HKEY_USERS:
				printf("It's HKEY_USERS, 0x%x \n", hKey);
				break;
				
			case HKEY_CURRENT_CONFIG:
				printf("hkey: HKEY_CURRENT_CONFIG: %x \n", hKey);
				break;
			
			default:
				printf("Notice:");
				printf("Less expected hKey '0x%x', the known ones are: \n", hKey);
				printf(" HKEY_CLASSES_ROOT   | Integer value: 80000000 \n");
				printf(" HKEY_CURRENT_USER   | Integer value: 80000001 \n");
				printf(" HKEY_LOCAL_MACHINE  | Integer value: 80000002 \n");
				printf(" HKEY_USERS          | Integer value: 80000003 \n");
				printf(" HKEY_CURRENT_CONFIG | Integer value: 80000005 \n");
				printf("For more information consult: https://docs.microsoft.com/en-us/windows/win32/sysinfo/predefined-keys \n");
				
		}
		
	}
		
		
		
	if (error == ERROR_FILE_NOT_FOUND) {
		printf("Registry key cannot be found or is incorrect.\n");
		}
}

// This source code is in Ansi mode.
void getRegistryKeyValue(){
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
					printf(TEXT("  [ERROR on line %d]: \n   The Windows Registry '%s' subkey could not be opened. \n   Error code: %x\n"), __LINE__, lpSubKey, error );
					
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
