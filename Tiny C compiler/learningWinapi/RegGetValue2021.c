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
void registryHiveInterpretation();

    // For hKey argument
	// Makes Accept both hex values, integer values and string values
	// HKEY_LOCAL_MACHINE       80000002      0x80000002
void main(){
	getRegistryKeyValue();
}



void openRegistryKey(
	HKEY   hKey,
	LPCSTR lpSubKey,
	DWORD  ulOptions,
	REGSAM samDesired,
	PHKEY  phkResult){
	  
	
	// Pointer to opened registry key
	HKEY openedHkey;
	  
	  
	  
	// https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa
	LONG error = RegOpenKeyExA(
		hKey      = HKEY_CURRENT_CONFIG,
		lpSubKey  = "System",	  
		ulOptions = 0,
		samDesired = KEY_READ,
		phkResult = &openedHkey
	);
	
		printf("Registry hive:   ");
		registryHiveInterpretation(hKey);
		printf("Registry subkey: \\%s \n", lpSubKey);
		printf("phkResuslt: %x \n", *phkResult);
	
	if (error == ERROR_SUCCESS) {
		printf("The registry subkey has been opened successfully\n");
				
		
	}
		
		
		
	if (error == ERROR_FILE_NOT_FOUND) {
		printf("Registry subkey cannot be found or is incorrect.\n");
		}
		
		
	error = RegCloseKey(openedHkey);
	if (error == ERROR_SUCCESS) {
		printf("The registry subkey has been closed successfully\n ");
	} else {
		printf("Error code: %x    Consult the Microsoft documentation to understand the error. https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regclosekey  \n", error);
		//
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
		// Variable is overwritten when returning, so making a macro that holds the initial value would be needed, to preserve the value after the function return.
		// https://stackoverflow.com/questions/26069085/visual-c-reggetvalue-fails-in-program-where-it-shouldnt/26069277#26069277
		DWORD BufferSize;
		
		// Holds the type of the registry key value
		DWORD valueType;
	
		// Error Codes Handling
		LONG error;
	
		// RegGetValue, Retrieves the type and data for the specified registry value. https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-reggetvaluea
		error = RegGetValueA(
			hkey     = HKEY_LOCAL_MACHINE,
			lpSubKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",
			lpValue  = "Path",
			dwFlags  = RRF_RT_ANY,
			pdwType  = &valueType, // This default NULL value, states that we do not request specific registry value type  https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry-value-types
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
		// Needs enumeration
		printf(TEXT("  pdwType: %i https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-rprn/25cce700-7fcf-4bb6-a2f3-0f6d08430a55 \n"), pdwType);
		
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


// Manual enumeration
void registryHiveInterpretation(hKey){
	switch ((int) hKey){
		case HKEY_CLASSES_ROOT:
			
			printf("HKEY_CLASSES_ROOT: 0x%x \n", hKey);
			break;
			
		case HKEY_CURRENT_USER:
			printf("HKEY_CURRENT_USER: 0x%x \n", hKey);
			break;
			
		case HKEY_LOCAL_MACHINE:
			printf("HKEY_LOCAL_MACHINE: 0x%x \n", hKey);
			break;
			
		case HKEY_USERS:
			printf("HKEY_USERS: 0x%x \n", hKey);
			break;
			
		case HKEY_CURRENT_CONFIG:
			printf("HKEY_CURRENT_CONFIG: %x \n", hKey);
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

