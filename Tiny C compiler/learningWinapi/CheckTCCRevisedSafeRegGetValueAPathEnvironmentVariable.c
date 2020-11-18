#pragma comment(lib, "advapi32") // No more Need for tcc -ladvapi32 RegGetValueA.c  error: undefined symbol 'RegGetValueA' 
#include <stdio.h>               // Prevents a warning:                             warning: implicit declaration of function 'printf'
#include <windows.h>             // Required, else an error:                        error: 'DWORD' undeclared

#include <stdlib.h>              // Gives access to Malloc, And  Prevents:          warning: implicit declaration of function 'malloc'
                                 //                 Calloc,                         warning: cast between pointer and integer of different size
                                 //                 Realloc 


/*

             Required, else an error: 
      "error: undefined symbol 'RegGetValueA'"
      
 Proper compilation method/tutorial 
   tcc -impdef advapi32.dll -o .\lib\advapi32.def
   tcc -ladvapi32 RegGetValueAPathEnvironmentVariable.c


*/

/*              References
               pvData-split
      https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
*/

void main(){
    DWORD BufferSize = 0;
    
    HKEY    hkey     = HKEY_LOCAL_MACHINE;
    LPCSTR  lpSubKey = "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";
    LPCSTR  lpValue  = "Path";
    DWORD   dwFlags  = RRF_RT_ANY;
    LPDWORD pdwType  = NULL;
    PVOID   pvData   = NULL;
    LPDWORD pcbData  = &BufferSize;
    
    // First, RegGetValueA retrieves pcbData, which contains size of pvData in bytes
    RegGetValueA(hkey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
    
    // Allocate Memory for pvData | Returns address for pvData to use
    pvData = (int*)malloc(*pcbData);
    
    // Second, RegGetValueA retrieves pvData, which contains path variable value
    RegGetValueA(hkey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
    
        puts("___________________[pvData]___________________");
        puts(pvData);
        puts("________________[pvData-split]________________");
		puts("Not working properly, needs checking for directory and correct placement of \\\\");
		puts("Not working properly, C:\\Program Files (x86) contains space, needs sanitation");
		puts("Not true, everything works, the emptyString had too little space allocated");
		char *token = strtok(pvData, ";"); 
		while (token != NULL) 
		{ 
	
		FILE *file;
		char filename[50] = "\\tcc.exe";
		char emptyString[90];
		emptyString[0] = '\0';
		strcat(emptyString, token);
		strcat(emptyString, filename);
		printf("Concatinated: ");
		printf(emptyString);
		printf("\n");
		
		if (file = fopen(emptyString, "r")){
			fclose(file);
			printf("yes");
			
		}	
	
			//printf("%s\n", token); 
			token = strtok(NULL, ";"); 
		} 
        puts("___________________[Debug]____________________");
        printf("  Retrieved information about array size: %i\n",*pcbData);
        printf("  Actual size of the array: %i\n", strlen(pvData));
        printf("  Manually Allocated bytes for the array: %zu", sizeof(pvData));
        printf("\n  (Since malloc was used, the dynamic Allocation makes the Manual Allocation results strange.)\n");
        // https://stackoverflow.com/questions/37447198/dynamically-allocated-variable-size        // https://stackoverflow.com/questions/37447198/dynamically-allocated-variable-size
    
    free(pvData);
}
