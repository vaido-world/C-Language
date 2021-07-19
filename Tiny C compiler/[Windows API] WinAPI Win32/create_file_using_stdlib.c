/**
 * C program to create a file and write data into file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_SIZE 1000

char * get_environment_variable(char * Environment_Variable);
int main()
{

    /* File pointer to hold reference to our file */
    FILE * fPtr;
	

	// TODO: https://www.programmersought.com/article/71016309795/ REPLACE / with //!
	// TODO: Add malloc
	// TODO: Return multiple values of the array
	// TODO: 
	char * returning = get_environment_variable("USERPROFILE");

	printf("test2: %s\n", returning);
	
	#define filenamelength 100
	strncat(returning, "\\tccs.cmd", filenamelength);
	
	
    /* 
     * Open file in w (write) mode. 
     * "tcc.cmd" is complete path to create file
     */
    fPtr = fopen(returning, "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }


    /* Write data to file */
    fputs("@ECHO OFF\n", fPtr);
    fputs("tcc.exe", fPtr);


    /* Close file to save file data */
    fclose(fPtr);


    /* Success message */
    printf("File created and saved successfully. :) \n");


    return 0;
}



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// https://stackoverflow.com/questions/11656532/returning-an-array-using-c/27237843#27237843
// https://stackoverflow.com/questions/33459843/c-returning-string-array/33459881#33459881
// https://stackoverflow.com/questions/8144917/returning-a-2d-char-array-in-c/8145063#8145063 
char * get_environment_variable(char * Environment_Variable){
	static char * static_array[1];
	
	if (getenv(Environment_Variable)) {
		char * Environment_Variable_Value = getenv(Environment_Variable);
		int    Environment_Variable_Length_In_Bytes = strlen(Environment_Variable_Value);

			char newstr[ 30 * sizeof(Environment_Variable_Value) ]; // As suggested by "chux" - ensure buffer is big enough!
			int i, j;
			for (i = j = 0; i < (int)strlen(Environment_Variable_Value); i++, j++) {
				newstr[j] = Environment_Variable_Value[i];
				if (Environment_Variable_Value[i] == '\\') newstr[++j] = '\\'; // Insert extra backslash
			}
			newstr[j] = '\0'; // We need to add nul-terminator!

			#define filenamelength 10
			strncat(newstr, "\\tccs.cmd", filenamelength);
			
	
		static_array[0] = Environment_Variable_Value;
		
		
		//printf("Environment_Variable: %s\n", Environment_Variable);
		//printf("Environment_Variable_Value: %s \n", Environment_Variable_Value);
		//printf("Environment_Variable_Length_In_Bytes: %i \n", Environment_Variable_Length_In_Bytes);
	} else {
		printf("'%s' Environment Variable is not found.", Environment_Variable);		
	}
	
	printf("", static_array); // Buggy, removing no return happens.
	return * static_array;
}
