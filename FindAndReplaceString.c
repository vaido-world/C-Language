// C program to search and replace 
// all occurrences of a word with 
// other word. https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
// Function to replace a string with another 
// string 


char* replaceWord(const char* stringInput, 
                  const char* searchWord, 
                  const char* replacementWord) 
{ 
    char* result; 
    
    int replacementWordLength = strlen(replacementWord); 
    int searchWordLenght = strlen(searchWord); 
    const char terminationCharacter = '\0';    
    
    // Loop through the whole input string 
    // Counting the number of times old word 
    // occur in the string
    int i;
    int occurences;
    for (i = 0, occurences=0; stringInput[i] != terminationCharacter; i++) { 
        //Counting Occurences in the Input Array that contain strings.
        if (strstr(&stringInput[i], searchWord) == &stringInput[i]) { 
            occurences++; 
  
            // Jumping to index after the old word. 
            i += searchWordLenght - 1; 
        } 
    } 
  
    //-------------------------------------------------------
    
    // After counting Occurences
    // Allocating memory for the result variable
    // Making new string of enough length 
    result = (char*)malloc(
                           i + occurences * (replacementWordLength - searchWordLenght) + 1
     ); 
  
    
    // Loop stringInput and replace words
    i = 0; 
    while (*stringInput) { 
        // Compare the substring with the result 
        if (strstr(stringInput, searchWord) == stringInput) { 
        
            // Copy string to the result array
            strcpy(&result[i], replacementWord); 
            
            // Add length of replacement word to the Loop increment
            i += replacementWordLength; 
            
            // After adding a string, increase an array length
            // Add searchWordLenght to the String Input???
            stringInput += searchWordLenght; 
        } 
        else
            // If stringInput does not match searchable word
            // Set result item to the stringInput item 
            result[i++] = *stringInput++; 
    } 
    // Add terminationCharacter at the end of result array
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
