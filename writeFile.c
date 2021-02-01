#include <stdio.h>
void main(){
	FILE *filePointer = fopen ("file.txt", "w+");
	fprintf(filePointer, "%s %s %s %d", "We", "are", "in", 2012);
	fclose(filePointer);
}