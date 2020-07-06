#include <stdio.h>  // printf(), gets(), puts()
#include <stdlib.h> // malloc()
#include <string.h> // strcmp(), strcpy()

/* FILENAME: interpreter.c
   DESCRIPTION: A poor Shell/Command Prompt for Operating Systems.
*/


// Function To Compare strings 
int equals(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

// Function to Return String
char* get_message ()
{
    char *mymessage = malloc (sizeof(char));
    strcpy(mymessage, "Hello World");
    return mymessage;
}
   //printf(get_message());


// TODO: When Comparing ignore Spaces, TABs and New Lines   
// TODO: Check if a word before and after contains enough characters to be interpreted.
//       If contains, interpret the word.
int main( ) {
   // Declare Char variable as Dynamic Memory Allocated Array to be used as a String.
   char* text = malloc(sizeof(char));
   
   // Compare Strings
   if (equals("asdf", "asdfd")){
	   
	   printf("yes");
   } else {
	   
	   printf("no");
   }

   // Capture User Input by Reading Command Line
   printf( "Enter a value :");
   gets( text );

   // Show Captured User Input by 
   printf( "You entered: ");
   puts( text );
   
   // Stop program from closing and request to press Enter.
   gets(" ");
   return 0;
}


// Returning Strings/Char Arrays in Functions
// https://www.linuxquestions.org/questions/programming-9/c-returning-char-array-pointer-4175490314/#post5092880

// String Comparison 
// https://stackoverflow.com/questions/16480971/strcmp-as-substitute-for/16481220#16481220
