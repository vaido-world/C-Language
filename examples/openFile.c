/*

Filename: openFile.c
Description: An example for reading a text file. (that is script's source file itself) 
Usage: 
	tcc -run openFile.c
		This file is a test file and should be run and used as script, and not compiled to a binary.
Notes:
	If compiled to executable, the executable still opens file "openFile.c" instead of "openFile.exe".
	If compiled to executable, and there is no file named "openFile.c" in the same folder, nothing will happen.
General Overview:
	Opens a __File__
	Reads BufferLine [of size CHAR_MAX] from openedFile
	Prints bufferLine
	Closes openedFile
*/
#include <stdio.h>
#include <limits.h>
void main(){
	FILE *openedFile = fopen(__FILE__, "r");
	char bufferLine[CHAR_MAX];
	while (fgets(bufferLine, CHAR_MAX, openedFile)){
		printf("%s", bufferLine );
	}
	fclose(openedFile);
}

// aaaaaaaaaaaaaaaaaaaaaaaaadddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaadddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaadddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaddddddddddddddddddddddddddddddd


	//char lineLength;
	//char maximumCharacters;

	// after finding #character, return only 5 characters after it
	//strchr()
	//fgets()
	// WriteOperation

		//printf("1 : %s\n", buff );
		//
		//fgets(buff, 255, (FILE*)fp);
		//printf("2: %s\n", buff );
		//
		//fgets(buff, 255, (FILE*)fp);
		//printf("3: %s\n", buff );
	