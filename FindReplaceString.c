/*
A program to replace a string/word with another in a line of text/input.
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


// Usage Example: 
// replaceWord("Hello World", "World", "Earth");
char* replaceWord(const char* stringInput, 
                  const char* searchWord, 
                  const char* replaceWord) 
{ 
    // Program constants
    const char terminationCharacter = '\0'; 
    // + 1  is for the \0 character in the string array
    const int terminationCharacterLength = 1; 
    
    // Chapter 1 [Allocating Memory] 
    
    // Counting the characters in the variables
    int searchWordLength = strlen(searchWord);
    int replaceWordLength = strlen(replaceWord);
    
    // Counting Occurences in the stringInput
    int i;
    int occurences;
    
    printf("xx is replace word, so it is jumped over\n               ---\n"); // Look for comment: "Jumping to index after the old word."
    for (i = 0, occurences=0; stringInput[i] != terminationCharacter; i++) { 
        // If the stringInput Token matches Search word:
        printf("%s | stringInput[%i]\n", &stringInput[i], i);
        // Scans for occurence of searchWord in the current InputString[i], 
        // strstr Returns a pointer to the first occurrence
        // We compare the returned pointer address with ...? the leftover string Address?
        if (strstr(&stringInput[i], searchWord) == &stringInput[i]) { 
            occurences++;
            
            // Jumping to index after the old word. 
            i += searchWordLength - 1; 
        }
    }
    
    // Chapter 2 [Allocating Memory] 
    
    // Allocating memory for the result variable
    // Making new string of enough length 
    // i          - The overall counted tokens in the stringInput
    // occurences - The counted occurences stringInput
    
    // (replaceWordLength - searchWordLength) 
    
    
    printf("replaceWordLength - %i, searchWordLenght - %i\n",  replaceWordLength, searchWordLength);
    printf("i - %i, occurences - %i\n", i, occurences);
    // Look further: C Operator Precedence (c language arithmetic operators evaluation order)
  

    char* result;
    result = (char*)malloc(
                           i + occurences * (replaceWordLength - searchWordLength) + terminationCharacterLength
     ); 
     
     // occurences * (replaceWordLength - searchWordLength) + 17
     printf("result: %i\n", result);
     
     
     
     
    // Chapter 3 [Replacing Words] 
    // Loop stringInput and replace words
    i = 0; 
    while (*stringInput) { 
        // Compare the substring with the result 
        if (strstr(stringInput, searchWord) == stringInput) { 
        
            // Copy string to the result array
            strcpy(&result[i], replaceWord); 
            
            // Add length of replacement word to the Loop increment
            i += replaceWordLength; 
            
            // After adding a string, increase an array length
            // Add searchWordLenght to the String Input???
            stringInput += searchWordLength; 
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
