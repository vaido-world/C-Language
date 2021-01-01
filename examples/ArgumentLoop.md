### A weird inconsistency when using printf on an Empty Array Item
On Linux
When the argument of the parameter is empty (NULL) - It is replaced with `"SHELL=/bin/bash"`

On Windows
Seems to be replaced with `(null)`

####



`tcc -run ArgumentLoop.c -compile `
```
[The interpretation of Argument Loop.] 
 0,  BaseArgument: ArgumentLoop.c
 1,  parameter: -compile
 2   Argument:  (null)
```

```
tcc -run ArgumentLoop.c -compile dsf
[The interpretation of Argument Loop.] 
 0,  BaseArgument: ArgumentLoop.c
 1,  parameter: -compile
 2   Argument:  dsf
```

```
tcc -run ArgumentLoop.c 
[The interpretation of Argument Loop.] 
 0,  BaseArgument: ArgumentLoop.c
 1,  parameter: -compile
 2   Argument:  SHELL=/bin/bash
```


#### Test subject
```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Example:  tcc -run BooleanTest.c -compile tcc sdf



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
```
