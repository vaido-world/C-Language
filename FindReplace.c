#include <string.h>
#include <stdlib.h>

char* replace(
	char const* inputString,
	char const* searchString,
	char const* replaceString	
){
	size_t const inputStringLength   = strlen(inputString);
	size_t const searchStringLength  = strlen(searchString);
	size_t const replaceStringLength = strlen(replaceString);
	
	
	// Find searchString Occurences in the inputString
	size_t      searchStringFound = 0;
	const char* pointerToInputString;
	for (pointerToInputString = inputString; 
	     searchStringLocation = strstr(pointerToInputString, searchString); 
		 next = patloc + patlen
	){
		
		
	}
}



void main(){
	
	
}

// Rewrite source: https://stackoverflow.com/questions/779875/what-function-is-to-replace-a-substring-from-a-string-in-c/780024#780024
