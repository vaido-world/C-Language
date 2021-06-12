#pragma comment(lib, "advapi32") // No more Need for tcc -ladvapi32 RegGetValueA.c  error: undefined symbol 'RegGetValueA' 
#include <stdio.h>               // Prevents a warning:                             warning: implicit declaration of function 'printf'
#include <stdlib.h>              /* Gives access to Malloc, And  Prevents:          warning: implicit declaration of function 'malloc'
                                                    Calloc,                         warning: cast between pointer and integer of different size
                                                    Realloc 
                                 */
#include <windows.h>             // Required, else an error:                        error: 'DWORD' undeclared

/*
        Proper compilation method/tutorial 
             Required, else an error: 
	  "error: undefined symbol 'RegGetValueA'"
	  
   1. tcc -impdef advapi32.dll -o .\lib\advapi32.def                                error: undefined symbol 'RegGetValueA' 
   2. tcc -ladvapi32 RegGetValueAPathEnvironmentVariable.c | Not needed anymore, 
														   | since the pragma comment is defined above.


*/


// Continue studying 
// https://www.google.com/search?sxsrf=ALeKk01YX5iJvh5ok3PNKGCM5tOj9DZmlw%3A1602854754213&ei=Yp-JX7rUDPiHwPAPyeyc8Ao&q=c+language+undefined+behavior+mistakes&oq=c+language+undefined+behavior+mistakes&gs_lcp=CgZwc3ktYWIQAzoECAAQRzoJCAAQyQMQFhAeOggIIRAWEB0QHjoFCCEQoAE6BwghEAoQoAFQ7jhY_Ulg40poAXACeACAAXaIAbsHkgEDNy4zmAEAoAEBqgEHZ3dzLXdpesgBCMABAQ&sclient=psy-ab&ved=0ahUKEwi6jYGim7nsAhX4AxAIHUk2B64Q4dUDCA0&uact=5

#define getPathVariableFromRegistry main 
void getPathVariableFromRegistry(){


	// Exchange Buffer 
    #define BUFFER  8192
    DWORD BufferSize = BUFFER;
    
	// Getting the size of value that will be returned
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
	
	// Allocating enough space for the Value that will be Returned
    pvData = (int*)malloc(*pcbData);
    
	
	// Getting the Value from the Key in the Registry
    RegGetValueA(
        hkey,
        lpSubKey,
        lpValue,
        dwFlags,
        pdwType,
        pvData,
        pcbData
    );
    
        puts("                  ---");
        printf("%s \n", pvData);
        puts("                  ---");
        printf("\nRetrieved information about array size: %i\n",*pcbData);
        printf("Actual size of the array: %i\n", strlen(pvData));
        printf("Manually Allocated bytes for the array: %zu", sizeof(pvData));
        printf("\nSince malloc was used, the dynamic Allocation makes the Manual Allocation results strange.");
        // https://stackoverflow.com/questions/37447198/dynamically-allocated-variable-size
    
    
}
