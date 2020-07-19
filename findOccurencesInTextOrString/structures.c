#include <stdio.h> 
#include <stdio.h>
#include <string.h>


struct OccurencesOutput { 
    int returnValue;
	int occurrenceStartPosition;
	int occurrenceEndPosition;
}; 
  
typedef struct OccurencesOutput Struct; 
  
  

Struct findNextTextPosition(char haystack[], char needle[]){
	Struct s;
	
	static int searchStartPosition;
	       int searchEndPosition = strlen(haystack);
	
	char * occurrence = strstr(haystack + searchStartPosition, needle);
	s.occurrenceStartPosition = occurrence-haystack;
	s.occurrenceEndPosition   = s.occurrenceStartPosition + strlen(needle);
		
	if (searchStartPosition <= searchEndPosition){
		searchStartPosition += s.occurrenceEndPosition;
		s.returnValue = 1;
		return s;
		
	} else {
		s.returnValue = 0;
		return s;
	}
	
}
  
int main() 
{ 
while(findNextTextPosition("test test teeeest", "st").returnValue){
	printf("%i\n", findNextTextPosition("test test teeeest", "st").occurrenceStartPosition);
	// findNextTextPosition("test test teeeest", "st").next;
	findNextTextPosition().returnValue;
}
  
    return 0; 
} 