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
	  https://www.geeksforgeeks.org/how-to-append-a-character-to-a-string-in-c/
	  https://eklitzke.org/declaring-c-string-constants-the-right-way
	  https://stackoverflow.com/questions/21638303/do-i-need-to-change-the-size-of-my-char-pointer-every-time-i-change-its-content/21638422#21638422
	  https://stackoverflow.com/questions/1495368/strtok-and-memory-leaks/1495374#1495374
	  https://stackoverflow.com/questions/2259890/using-sizeof-on-mallocd-memory/2259897#2259897
	  https://stackoverflow.com/questions/2259890/using-sizeof-on-mallocd-memory/2259909#2259909
	  https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation#:~:text=In%20the%20Windows%20API%20(with,and%20a%20terminating%20null%20character.
*/

#define TERMINATING_CHARACTER_SIZE 1

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
	printf("%i",*pcbData);
	getchar();
	

    
    // Second, RegGetValueA retrieves pvData, which contains path variable value
    RegGetValueA(hkey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
    
        puts("___________________[pvData]___________________");
        puts(pvData);
        puts("________________[pvData-split]________________");
		puts("Not working properly, needs checking for directory and correct placement of \\\\");
		puts("Not working properly, C:\\Program Files (x86) contains space, needs sanitation");
		puts("Not true, everything works, the emptyString had too little space allocated");
		puts("Not true, everything works, no need for checking if directory or not, executes properly even with double backslashes");
		puts("C:\\ is lower priority than C:\\Windows directory,but higher than C:\\Users\\user\\Desktop");
		puts("Make priority for executables by folder location");
		puts("Not true, the priority depends on the position in the path variable");
		puts("Requires Dynamic Memory Allocation support.");
		
		
		puts("char *token       is a pointer address to pvData");
		puts("strtok only returns a pointer to a location inside the string you give it as input-- it doesn't allocate new memory for you");
		puts("https://stackoverflow.com/questions/1495368/strtok-and-memory-leaks/1495374#1495374");
		printf("The size of pvdata is pcbData %i bytes\n", *pcbData);
        printf("\n   |-> (sizeof operator only finds the size of a variable in bytes at compile time.)");
        printf("\n   |-> (To know the size of heap-allocated memory, you need to keep track of it manually, sizeof won't help you.)");
        printf("\n   |-> (https://stackoverflow.com/questions/2259890/using-sizeof-on-mallocd-memory/2259897#2259897)");

		char *token = strtok(pvData, ";"); 
		while (token != NULL) 
		{ 
	
		FILE *file;
		const char filename[] = "\\tcc.exe";
		printf("filename size: %i\n", sizeof(filename));
		printf("token size: %i\n", sizeof(token));
		

		char emptyString[90];
		emptyString[0] = '\0';
		strcat(emptyString, token);
		strcat(emptyString, filename);
		printf("Concatinated: ");
		printf("%i\n", sizeof(emptyString));
		printf("strln: %i\n", strlen(emptyString)+TERMINATING_CHARACTER_SIZE);
		printf(emptyString);
		printf("\n");
		//getchar();
		if (file = fopen(emptyString, "r")){
			fclose(file);
			printf("yes\n");
			
		}	
	
			//printf("%s\n", token); 
			token = strtok(NULL, ";"); 
		} 
        puts("___________________[Debug]____________________");
        printf("  Retrieved information about array size: %i\n",*pcbData);
        printf("  Actual size of the array: %i\n", strlen(pvData));
        printf("  Manually Allocated bytes for the array: %zu", sizeof(pvData));
        printf("\n   |-> (sizeof operator only finds the size of a variable in bytes at compile time.)");
        printf("\n   |-> (To know the size of heap-allocated memory, you need to keep track of it manually, sizeof won't help you.)");
        printf("\n   |-> (https://stackoverflow.com/questions/2259890/using-sizeof-on-mallocd-memory/2259897#2259897)");
        //        https://stackoverflow.com/questions/37447198/dynamically-allocated-variable-size
    
    free(pvData);
}
