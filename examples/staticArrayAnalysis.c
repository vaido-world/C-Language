#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){
	
   printf("Array elements: %i\n\n" ,argc);
   puts("____________________________");
   
   int arraySizeInBytes;
   for (int i = 0; argc != 0; argc--, i++){
	   printf("%i | size: %i | Output: %s\n", i, strlen(argv[i]), argv[i]);
	   arraySizeInBytes += strlen(argv[i]);
   }
   puts("--------------------");
   printf("arraySizeInBytes: %i \n", arraySizeInBytes);
   

   return 0;
}

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
// tcc -run tests.c FirstArgument SecondArgument ThirdArgument
   
   
   
   
   
//    char filename[30];   
//strcpy(filename, argv[0]);
 //  printf("\nfilename: %s\n", argv[0]);
 //  printf("filename: %s\n", filename);