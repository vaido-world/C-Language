// C program to search and replace 
// all occurrences of a word with 
// other word. https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
// Function to replace a string with another 
// string 


char* replaceWord(const char* stringInput, 
                  const char* originalWord, 
                  const char* replacementWord) 
{ 
	char* result; 
	
    int replacementWordLength = strlen(replacementWord); 
    int originalLenght = strlen(originalWord); 
	const char terminationCharacter = '\0';	
	
	// Loop through the whole input string 
    // Counting the number of times old word 
    // occur in the string
    int i;
	int occurences;
    for (i = 0, occurences=0; stringInput[i] != terminationCharacter; i++) { 
		//Counting Occurences in the Input Array that contain strings.
        if (strstr(&stringInput[i], originalWord) == &stringInput[i]) { 
            occurences++; 
  
            // Jumping to index after the old word. 
            i += originalWordLenght - 1; 
        } 
    } 
  
    //-------------------------------------------------------
  
    // Making new string of enough length 
    result = (char*)malloc(
						   i + occurences * (replacementWordLength - originalWordLenght) + 1
	 ); 
  
    i = 0; 
    while (*stringInput) { 
        // compare the substring with the result 
        if (strstr(stringInput, originalWord) == stringInput) { 
		
            strcpy(&result[i], replacementWord); 
            i += replacementWordLength; 
			
            stringInput += originalWordLenght; 
        } 
        else
            result[i++] = *stringInput++; 
    } 
  
    result[i] = terminationCharacter; 
    return result; 
} 
  
// Driver Program 
int main() 
{ 
    char input[] = "xxforxx xx for xx"; 
    char word[] = "xx"; 
    char replacement[] = "Geeks"; 
  
    char* result = NULL; 
  
    // originalWord string 
    printf("Old string: %s\n", input); 
  
    result = replaceWord(input, word, replacement); 
    printf("New String: %s\n", result); 
  
    free(result); 
    return 0; 
} 