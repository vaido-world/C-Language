#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Example:  tcc -run BooleanTest.c -compile tcc sdf
//Example:  tcc -run ArgumentLoop2.c asd -compile tcc filename

void main(int argc, char *argv[]){
	if ( argv[1] == NULL ) {argv[1] = "-compile"; argc++;}
	
	printf("[The interpretation of Argument Loop.] \n");
	
	for (int index = 0; index < argc; index++){
		
		if (argv[index][0] == '-'){ 
			printf("\n %i,  parameter: %s", index, argv[index]); 
		} else { 
			if (index == 0){
				printf(" %i,  BaseArgument: %s", index, argv[index]); 
			} else {
				printf("\n %i,  BaseArgument: %s", index, argv[index]); 
				if (index == argc-1){ printf(" (The last element)");}
				
			}
		}
		if(strcmp(argv[index], "-compile") == 0) {
			printf( "\n %i   Argument:  %s", index, argv[++index]);
			}
		

		
		
	}
	
	

	

}



	// int option = 0;
	// int argument = 0;
	// if (option){
	// 	printf("An option");
	// }
	// if (argument){
	// 	printf("An argument");
	// }
	
	
		// if (argv[index][0] == '-'){ option=1; }
		// if (option){
		// 	printf(" %i, %s\n", index, argv[index]);
		// 	
		// } else {
		// 	printf(" %i, %s\n", index, argv[index]);
		// 	
		// }