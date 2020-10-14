#pragma comment(lib, "advapi32") // No more Need for tcc -ladvapi32 RegGetValueA.c  error: undefined symbol 'RegGetValueA' 
#include <stdio.h>               // Prevents a warning:                             warning: implicit declaration of function 'printf'
#include <windows.h>             // Required, else an error:                        error: 'DWORD' undeclared

#include <stdlib.h>              // Gives access to Malloc, And  Prevents:          warning: implicit declaration of function 'malloc'
                                 //                 Calloc,                         warning: cast between pointer and integer of different size
                                 //                 Realloc 


/*                               // Required, else an error:                        error: undefined symbol 'RegGetValueA'
 Proper compilation method/tutorial 
   tcc -impdef advapi32.dll -o .\lib\advapi32.def
   tcc -ladvapi32 RegGetValueAPathEnvironmentVariable.c


*/

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
	
	pvData = malloc(1);
    
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
