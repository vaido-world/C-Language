#include <stdlib.h>
#include <stdio.h>

// Look for Header files definitions in source files
// If header is used in a source file, 
// search for a .c source file around header location 
// and then outer-folder and outer-folder subfolders.

int main(){
	system("tcc -run .\\program\\*.c \
										");
	return 0;
}