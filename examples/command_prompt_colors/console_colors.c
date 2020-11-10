  #include<stdio.h>
#pragma comment(lib,"ws2_32") //Winsock Library
#include<stdio.h>
#include<winsock2.h>

int main(int argc , char *argv[])
{
 printf("I'm BLUE ");
	 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(hStdOut, (FOREGROUND_INTENSITY));

  printf("I'm BLUE ");
    SetConsoleTextAttribute(hStdOut, (COMMON_LVB_REVERSE_VIDEO));
  printf("\nI'm Dark/Invisible ");	  
	  SetConsoleTextAttribute(hStdOut, (FOREGROUND_BLUE | BACKGROUND_GREEN));
  printf("\nI'm BLUEest ");
        SetConsoleTextAttribute(hStdOut, (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED));

  
  
	
}
