// C program to search and replace 
// all occurrences of a word with 
// other word. https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
// Function to replace a string with another 
// string 


char* replaceWord(const char* stringInput, 
                  const char* searchWordLenght, 
                  const char* replacementWord) 
{ 
	char* result; 
	
    int replacementWordLength = strlen(replacementWord); 
    int searchWordLenghtLenght = strlen(searchWordLenght); 
	const char terminationCharacter = '\0';	
	
	// Loop through the whole input string 
    // Counting the number of times old word 
    // occur in the string
    int i;
	int occurences;
    for (i = 0, occurences=0; stringInput[i] != terminationCharacter; i++) { 
		//Counting Occurences in the Input Array that contain strings.
        if (strstr(&stringInput[i], searchWordLenght) == &stringInput[i]) { 
            occurences++; 
  
            // Jumping to index after the old word. 
            i += searchWordLenghtLenght - 1; 
        } 
    } 
  
    //-------------------------------------------------------
  
    // Making new string of enough length 
    result = (char*)malloc(
						   i + occurences * (replacementWordLength - searchWordLenghtLenght) + 1
	 ); 
  
    i = 0; 
    while (*stringInput) { 
        // Compare the substring with the result 
        if (strstr(stringInput, searchWordLenght) == stringInput) { 
		
			// Copy string to the result array
            strcpy(&result[i], replacementWord); 
			
			// Add length of replacement word to the Loop increment
            i += replacementWordLength; 
			
			// Add searchWordLenghtLenght to the String Input???
            stringInput += searchWordLenghtLenght; 
        } 
        else
			// If stringInput does not match searchable word
			// Set result item to the stringInput item 
            result[i++] = *stringInput++; 
    } 
  
    result[i] = terminationCharacter; 
    return result; 
} 
  
// Driver Program 
int main() 
{ 
    char* result = NULL; 
    result = replaceWord("xxforxx xx for xx", "xx", "Geeks"); 
    printf("New String: %s\n", result); 
  
    free(result); 
    return 0; 
} 