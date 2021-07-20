#include <stdio.h>

main(){
	
#define stringSize 10
char myStrings[][stringSize] = { "one", "two", "three", "four", "five" };

size_t i = 0;
for( i = 0; i < sizeof(myStrings) / sizeof(myStrings[0]); i++)
{
    printf(myStrings[i]);
}
}