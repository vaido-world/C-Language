#include <stdio.h>
#include <string.h>


// https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
//
int findPosition(char haystack[], char needle[]){
	char * occurrence = strstr(haystack, needle);
	int position = occurrence-haystack;
	return position;
}



// zbpos - startPosition
int findnext(int zbpos, const char *haystack, const char *needle)
{
    char *p; 

    if (((p = strstr(haystack + zbpos, needle)) != NULL)){
        return p - haystack;
	}
    return -1;
	
	
}



/*

	int currentPositionLastCharacterPosition;
	int currentPositionReversePosition;
	int currentPositionFinalCharacterPosition;
	int ShiftedCurrentPosition;
	
	int CurrentEndPosition;
	int CurrentPositionEndingPosition;
	
	int CurrentEndingPosition;
	int CurrentStartingPosition;
	
	int CurrentPositionStart;
	int CurrentPositionEnd;
	int CurrentPositionMiddle;
*/

// Searches for a word and returns positions
int findNextWordPosition(char haystack[], char needle[]){
	static int startPosition;
	int endPosition=strlen(haystack);
	
	char * occurrence = strstr(haystack + startPosition, needle);
	int currentPosition = occurrence-haystack;
	
	if ( startPosition <= endPosition){
		startPosition += currentPosition + strlen(needle);
		return currentPosition;
		
	} else {
		
		printf("end\n");
		return 1;
	}
	
	
}


// struct Occurrence{
// 	int returnValue;
// 	char startPosition;
// 	char endPosition;
// 	
// };
// 
// struct Occurrence occur;


// Searches for a word/text and returns position
int findNextTextPosition(char haystack[], char needle[]){
	static int searchStartPosition;
	       int searchEndPosition = strlen(haystack);
	
	char * occurrence = strstr(haystack + searchStartPosition, needle);
	int occurrenceStartPosition = occurrence-haystack;
	int occurrenceEndPosition   = occurrenceStartPosition + strlen(needle);
		
	if (searchStartPosition <= searchEndPosition){
		searchStartPosition += occurrenceEndPosition;
		// occurrenceStartPosition
		return 1;
		
	} else {
		return 0;
	}
	
}

int functiontest(){
	
	
}


int main(){
//printf("%i", findnext(findnext(0, "word word", "rd") + strlen("rd"), "word word", "rd"));

//printf("%i\n", findNextWordPosition("test test teeeest", "st"));
//printf("%i\n", findNextWordPosition("test test teeeest", "st"));
//printf("%i\n", findNextWordPosition("test test teeeest", "st"));
//printf("%i\n", findNextWordPosition("test test teeeest", "st"));



while(findNextTextPosition("test test teeeest", "st")){
	printf("0");
	
}

//printf("%i\n", findNextTextPosition("test test teeeest", "st"));
//printf("%i\n", findNextTextPosition("test test teeeest", "st"));
//printf("%i\n", findNextTextPosition("test test teeeest", "st"));
//printf("%i\n", findNextTextPosition("test test teeeest", "st"));


}

int deprecated(){
	char string[] = "very interesting; paragraph.";
	char searchWord[] = "paragraph";
	char * occurrence = strstr(string, searchWord);
	int position = occurrence-string;
	printf("%i \n", position);



	for (int i=16; i < strlen(string); i++){
		if (string[i] == ';'){
			printf("%i %c \n", i, string[i]);
		}
		
	}
}