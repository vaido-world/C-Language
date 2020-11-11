#include<stdio.h>
#include<windows.h> //includes wincon.h

int main(int argc , char *argv[])
{
 //printf("I'm BLUE ");
//	 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 //
 // SetConsoleTextAttribute(hStdOut, (FOREGROUND_INTENSITY));
 //
 // printf("I'm BLUE ");
 //   SetConsoleTextAttribute(hStdOut, (COMMON_LVB_REVERSE_VIDEO));
 // printf("\nI'm Dark/Invisible ");	  
//	  SetConsoleTextAttribute(hStdOut, (FOREGROUND_BLUE | BACKGROUND_GREEN));
 // printf("\nI'm BLUEest ");
 //       SetConsoleTextAttribute(hStdOut, (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED));
 //       SetConsoleTextAttribute(hStdOut, (COMMON_LVB_UNDERSCORE));
 //
 
 int FOREGROUND_WHITE = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE, BACKGROUND_INTENSITY));
  printf("Hello to the program\n");
  
  
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE | COMMON_LVB_UNDERSCORE));
	printf("Underscore\n");
	SetConsoleTextAttribute(hStdOut, (COMMON_LVB_REVERSE_VIDEO));
	printf("Completely dark, both Foreground and Background\n");
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE | COMMON_LVB_REVERSE_VIDEO));
	printf("Reverse Background and foreground colors\n");
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE | FOREGROUND_INTENSITY));
	printf("Increased intensity foreground\n");
	
	printf(" ");
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE | COMMON_LVB_GRID_HORIZONTAL | COMMON_LVB_GRID_LVERTICAL| COMMON_LVB_UNDERSCORE));
	printf("A");
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE | COMMON_LVB_GRID_HORIZONTAL | COMMON_LVB_UNDERSCORE));
    printf(" grid around text");
    SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE | COMMON_LVB_GRID_LVERTICAL));
	printf(" \n");
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_RED));
	printf("Red text and black background\n");
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_GREEN));
	printf("Green text and black background\n");
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_BLUE));
	printf("Blue text and black background\n");
	
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_GREEN | FOREGROUND_BLUE));
	printf("Light-blue text and black background\n");
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_GREEN | FOREGROUND_RED));
	printf("Yellow text and black background\n");
	
	SetConsoleTextAttribute(hStdOut, (0x5));
	printf("Purple text and black background\n");
	
	SetConsoleTextAttribute(hStdOut, (0x8));
	printf("Gray text and black background\n");
	
	
	SetConsoleTextAttribute(hStdOut, (0x9));
	printf("Blue  text and black background\n");
	
	unsigned int sdf = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(hStdOut, (0x0a));
	printf("light-green\n");	
	
	SetConsoleTextAttribute(hStdOut, (0x0b));
	printf("light-blue\n");		
	
	SetConsoleTextAttribute(hStdOut, (0x0c));
	printf("light-red\n");		
	SetConsoleTextAttribute(hStdOut, (0x0d));
	printf("light-purple\n");		
	SetConsoleTextAttribute(hStdOut, (0x0e));
	printf("light-yellow\n");		
	SetConsoleTextAttribute(hStdOut, (0x0f));
	printf("light-white\n");		

	
	
	SetConsoleTextAttribute(hStdOut, (FOREGROUND_WHITE));
	printf("White foreground and Black background ");
  
	
}
