# C-Language-Tutorial

## 2021-07-29 Self contained Tiny C Compiler
http://ptspts.blogspot.com/2009/11/tiny-self-contained-c-compiler-using.html  
https://github.com/pts/pts-tcc  

https://repo.or.cz/tinycc/self_contained.git
 
## 2021-07-25 Pointer Strings versus Array Strings
https://stackoverflow.com/questions/11679050/c-string-function-strcopy-strcat-strstr-with-arrays-and-pointers/11679070#11679070  

https://www.youtube.com/watch?v=90gFFdzuZMw  
https://cboard.cprogramming.com/c-programming/180464-invalid-memory-access-when-passing-string-literals-argument.html#post1302476  

https://repo.or.cz/tinycc/self_contained.git

```
#include <stdio.h>
#include <string.h>


void fnc(char * string){

    char *pointer = strstr(string, "out");
    if (pointer != NULL) {
        memcpy(pointer, "in", 2);
        memmove(pointer + 2, pointer + 3, strlen(pointer + 3) + 1);
    }
    printf("%s\n", string);

	
	
}

int main(void) {
	char strings[80] = "cat is out roaming";
	// char strings[] = "cat is out roaming"; // works
	// char strings[] = ""; // works
	//fnc("cat is out roaming"); //  invalid memory access
	fnc(strings);
    return 0;
}
```



## 2021-07-24 Multicore, parallelism, and multithreading 

https://youtu.be/uA8X5zNOGw8


### Offtopic: About strsafe
https://news.ycombinator.com/item?id=20793157  
https://docs.microsoft.com/en-us/windows/win32/menurc/strsafe-ovw  
https://stackoverflow.com/questions/54922292/is-stringcbprintf-strsafe-h-part-of-the-winapi  
https://stackoverflow.com/questions/10970617/there-is-no-strsafe-h-in-mingw-what-to-use-instead/12474997#12474997  



#### Thread Creation in Linux using C
https://www.educative.io/edpresso/how-to-create-a-simple-thread-in-c  

#### Additional resources for Windows systems
https://docs.microsoft.com/en-us/cpp/parallel/multithreading-with-c-and-win32?view=msvc-160  
https://docs.microsoft.com/en-us/cpp/parallel/sample-multithread-c-program?view=msvc-160  



#### Example of a thread creation in Windows using C
https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads   
Without strsafe as tcc does not support strsafe.h header   
```
#include <windows.h>
#include <tchar.h>


#define MAX_THREADS 3
#define BUF_SIZE 255

DWORD WINAPI MyThreadFunction( LPVOID lpParam );
void ErrorHandler(LPTSTR lpszFunction);

// Sample custom data structure for threads to use.
// This is passed by void pointer so it can be any data type
// that can be passed using a single void pointer (LPVOID).
typedef struct MyData {
    int val1;
    int val2;
} MYDATA, *PMYDATA;


int _tmain()
{
    PMYDATA pDataArray[MAX_THREADS];
    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS]; 

    // Create MAX_THREADS worker threads.

    for( int i=0; i<MAX_THREADS; i++ )
    {
        // Allocate memory for thread data.

        pDataArray[i] = (PMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                sizeof(MYDATA));

        if( pDataArray[i] == NULL )
        {
           // If the array allocation fails, the system is out of memory
           // so there is no point in trying to print an error message.
           // Just terminate execution.
            ExitProcess(2);
        }

        // Generate unique data for each thread to work with.

        pDataArray[i]->val1 = i;
        pDataArray[i]->val2 = i+100;

        // Create the thread to begin execution on its own.

        hThreadArray[i] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            pDataArray[i],          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[i]);   // returns the thread identifier 


        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (hThreadArray[i] == NULL) 
        {
           ErrorHandler(TEXT("CreateThread"));
           ExitProcess(3);
        }
    } // End of main thread creation loop.

    // Wait until all threads have terminated.

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for(int i=0; i<MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
        if(pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;    // Ensure address is not reused.
        }
    }

    return 0;
}


DWORD WINAPI MyThreadFunction( LPVOID lpParam ) 
{ 
    HANDLE hStdout;
    PMYDATA pDataArray;

    TCHAR msgBuf[BUF_SIZE];
    size_t cchStringSize;
    DWORD dwChars;

    // Make sure there is a console to receive output results. 

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if( hStdout == INVALID_HANDLE_VALUE )
        return 1;

    // Cast the parameter to the correct data type.
    // The pointer is known to be valid because 
    // it was checked for NULL before the thread was created.
 
    pDataArray = (PMYDATA)lpParam;

    // Print the parameter values using thread-safe functions.

    WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

    return 0; 
} 



void ErrorHandler(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40) * sizeof(TCHAR)); 
   

    // Free error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
```


## 2021-07-23 Memory leaks, Undefined behaviour, out of bounds
https://stackoverflow.com/questions/413477/is-there-a-good-valgrind-substitute-for-windows
https://web.stanford.edu/class/cs343/resources/purify.pdf

https://github.com/milostosic/MTuner

### Engineer Man
https://www.youtube.com/watch?v=ytGATjX3nqc&list=PLlcnQQJK8SUg4C8syQ63d6o44dzt_vFls



## 2021-07-22 ASCII TO UTF-8
https://www.google.com/search?q=Moving+from+ASCII+to+UTF-8+in+c&sxsrf=ALeKk00oT0vdGIKMq3NIjCmmTNuO3KhZbg%3A1626949861741&ei=5Uj5YPTTLIKcrgSty5nIAQ&oq=Moving+from+ASCII+to+UTF-8+in+c&gs_lcp=Cgdnd3Mtd2l6EAMyCAghEBYQHRAeMggIIRAWEB0QHjIICCEQFhAdEB4yCAghEBYQHRAeMggIIRAWEB0QHjIICCEQFhAdEB4yCAghEBYQHRAeMggIIRAWEB0QHjIICCEQFhAdEB4yCAghEBYQHRAeOgcIABBHELADOgcIIxCuAhAnSgQIQRgAUPsCWOEIYJkKaABwA3gAgAF4iAHPBJIBAzQuMpgBAKABAaoBB2d3cy13aXrIAQjAAQE&sclient=gws-wiz&ved=0ahUKEwi02s3EvPbxAhUCjosKHa1lBhkQ4dUDCA4&uact=5

### Unicode_backlashes_conversion_in.c
Now Displays Unicode Characters.    
The ASCII version still can process search and replace the characters,   
but displaying them with printf was a hassle.    
This version resolves it.  

New Problem: Does not support emoji.

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>
#include <wchar.h>
#include <time.h>

void main(){
printf("
                _______
               |       |
               |       |
               |       |  _
               |_______| |_|
\n");
	printf("Initializing clock for measuring CPU time. \n");
    clock_t start, end;
    double cpu_time_used;
    start = clock();
	

	printf("Setting locale for the Command Prompt.\n");
	setlocale(LC_ALL, "");
	
	printf("Initializing text variable:\n");
	const wchar_t text[] = L"The text with šįėšūįė9š backlashes\\ \\";
	int text_size_in_bytes = sizeof(text);
	printf("_______________________________________________________\n");
	wprintf(L"text              :'%ls' \n", text);
	printf("text_size_in_bytes: %i bytes \n", text_size_in_bytes);



	
	printf("_______________________________________________________\n");
	//printf("\nDescription: ");
	//printf("Copies every character of the text into a new text variable \n");
	//printf("and checks if the character is a backslash. If it is: places additional backlash. \n");
	//printf("\n");
	//printf("Dynamic Memory Allocation is present to avoid Memory Leaks caused by Undefined Behaviour \n");
	//printf("of language specification. \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("Looping through every character of the text variable.\n");
	printf("Moving the character to a new_text variable.\n");
	printf("Checking if the character is a '\\' backlash.\n");
	printf("  If a '\\' backlash is found: \n");
	printf("    Adding the additional '\\' backlash to the new_text variable.\n\n\n");
	printf("_______________________________________________________\n");
	printf("character_position | text[character_position]");
	printf("\n_______________________________________________________\n");
	
	int character_position;
	wchar_t * new_text = (wchar_t*)malloc(sizeof(text));
	if (new_text == NULL) printf("Memory Allocation Failed.");
	int new_text_size_in_bytes = sizeof(text);
	int new_character_position;
	
	int backslash_count = 0;

	for (    character_position = 0, 
	     new_character_position = 0;  
		 
		 character_position < wcslen(text); 
	 
	         character_position++, 
	     new_character_position++){

		/* Prettier to print this way, can be removed*/
		if (character_position >= 10) printf("%i|", character_position);
		if (character_position < 10) printf("%i |", character_position);
		

		new_text[new_character_position] = text[character_position];
		
	
		if (text[character_position] == '\\') {
			printf("Backlash");
			backslash_count++;
			new_text[++new_character_position] = '\\';
			
			// tcc -b -run backlashes_conversion_in_ASCII.c
			new_text_size_in_bytes += sizeof(wchar_t);
			wchar_t * tmp = realloc(new_text, new_text_size_in_bytes);
			if (tmp == NULL)
			{
				// could not realloc, but orig still valid
			}
			else
			{
				new_text = tmp;
			}

		}
		
		wprintf(L"%c", text[character_position]);
		printf("\n");

		
	}
	
	new_text[new_character_position] = '\0'; // We need to add nul-terminator!
	

	wprintf(L"_______________________________________________________\n");
	wprintf(L"backslash_count: %i \n", backslash_count);
	wprintf(L"new_text: '%s'", new_text);
	wprintf(L"\n");
	wprintf(L"new_text_size_in_bytes: %i ", new_text_size_in_bytes);
	wprintf(L"\n");
	
	 end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	 printf("Program took %f seconds to execute. \n", cpu_time_used);
	printf("_______________________________________________________\n");
	
	free(new_text);
	new_text=NULL;
}

```


https://stackoverflow.com/questions/526430/c-programming-how-to-program-for-unicode/526494#526494

## 2021-07-21
https://www.codeproject.com/Articles/12532/Inject-your-code-to-a-Portable-Executable-file
https://stackoverflow.com/questions/2988038/default-values-on-arguments-in-c-functions-and-function-overloading-in-c/12094348#12094348

## 2021-07-20 Realloc common mistakes.
https://stackoverflow.com/questions/36923389/what-will-realloc-do-to-the-old-pointer/36923607#36923607
https://stackoverflow.com/questions/38213123/is-it-good-coding-practice-to-assign-the-address-returned-by-realloc-to-the-sa/38213241#38213241
https://stackoverflow.com/questions/44789295/correct-use-of-realloc/44789441#44789441

### Checking if realloc succeed
```
tmp = realloc(orig, newsize);
if (tmp == NULL)
{
    // could not realloc, but orig still valid
}
else
{
    orig = tmp;
}

```

### https://en.cppreference.com/w/c/memory/calloc#Return_value
> **On success**, returns the pointer to the beginning of newly allocated memory.   
> To avoid a memory leak, the returned pointer must be deallocated with free() or realloc().  
> **On failure**, returns a null pointer.  



### ASCII_backlashes_conversion_in.c
Based on:  
https://stackoverflow.com/questions/61125503/how-to-replace-a-backslash-with-two-backslashes-in-c-program/61125744#61125744
![image](https://user-images.githubusercontent.com/21064622/126502200-25e6ba7d-9d38-4eef-9674-72235cf5d5b0.png)


```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

void main(){
 
     clock_t start, end;
     double cpu_time_used;
     start = clock();
	
	
	
	printf("
	
 _______
|       |
|       |
|       |  _
|_______| |_|
	
	");
	
	char text[] = "The text with backlashes\\ \\";
	int text_size_in_bytes = sizeof(text);
	printf("_______________________________________________________\n");
	printf("text              :'%s' \n", text);
	printf("text_size_in_bytes: %i bytes \n", text_size_in_bytes);


	int character_position;

	char * new_text = (char*)malloc(sizeof(text));
	int new_text_size_in_bytes = sizeof(text);
	int new_character_position;
	
	int backslash_count = 0;
	
	printf("_______________________________________________________\n");
	printf("Description: ");
	printf("Copies every character of the text into a new text variable \n");
	printf("and checks if the character is a backslash. If it is: places additional backlash. \n");
	printf("\n");
	printf("Dynamic Memory Allocation is present to avoid Memory Leaks caused by Undefined Behaviour \n");
	printf("of language specification. \n");
	printf("\n_______________________________________________________\n");
	printf("character_position | text[character_position]");
	printf("\n_______________________________________________________\n");
	for (    character_position = 0, 
	     new_character_position = 0;  
		 
		 character_position < strlen(text); 
	 
	         character_position++, 
	     new_character_position++){

		/* Prettier to print this way, can be removed*/
		if (character_position >= 10) printf("%i|", character_position);
		if (character_position < 10) printf("%i |", character_position);
		

		new_text[new_character_position] = text[character_position];
		
	
		if (text[character_position] == '\\') {
			printf("Backlash");
			backslash_count++;
			new_text[++new_character_position] = '\\';
			
			// tcc -b -run backlashes_conversion_in_ASCII.c
			new_text_size_in_bytes += sizeof(char);
			char * tmp = realloc(new_text, new_text_size_in_bytes);
			if (tmp == NULL)
			{
				// could not realloc, but orig still valid
			}
			else
			{
				new_text = tmp;
			}

		}
		
		printf("%c", text[character_position]);
		printf("\n");

		
	}
	
	new_text[new_character_position] = '\0'; // We need to add nul-terminator!
	

	printf("_______________________________________________________\n");
	printf("backslash_count: %i \n", backslash_count);
	printf("new_text: '%s'", new_text);
	printf("\n");
	printf("new_text_size_in_bytes: %i ", new_text_size_in_bytes);
	printf("\n");
	
	 end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	 printf("Program took %f seconds to execute. \n", cpu_time_used);
	printf("_______________________________________________________\n");
}

	

```


### Modular project experiment with multiple main functions
This example will show that it is possible to make three different source files with main methods.
#### ModularProject.c
```
#define main main
#include "WindowProc2a.c"
#include "WindowProc3a.c"
void main() 
{ 	
	WindowProc2a();
	WindowProc3a();
	printf(__FILE__" \n");


} 
```
#### WindowProc2a.c
```
#ifndef main
#define WindowProc2a main
#endif

#include <stdio.h>
void WindowProc2a() 
{ 
	printf(__FILE__" \n");


} 
```
#### WindowProc3a.c
```
#ifndef main
#define WindowProc3a main
#endif

#include <stdio.h>
void WindowProc3a() 
{ 
	printf(__FILE__" \n");


} 
```
Results: they are all executable and can be included in each other and called when needed.  
Downside: Requires a lot of manual work to avoid the conflict between the main functions of each source file.   


## Experiment
The most main source file should look like this

```
#define main main
#define tes main

#include "RegGetPathValue.c"


// Redefine Main method



void tes(){
	printf("alrigdffffffffffffffffht");
	RegGetPathValue();

	
}
```


## 2021-05-31
https://stackoverflow.com/questions/61861026/how-does-the-c-standard-library-work-behind-the-scenes/61861971#61861971

## 2021-05-29
https://www-personal.acfr.usyd.edu.au/tbailey/ctext/ctext.pdf

## 2021-05-22
http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci493.73/csci493.73_spr10.php

## 2021-04-07
https://www.unf.edu/~wkloster/2220/ppts/cprogramming_tutorial.pdf

## 2021-03-25
https://scottc130.medium.com/writing-your-first-x86-program-3fd2b33139d6

## 2021-02-08
`tcc: error: -run is not available in a cross compiler`   
The reason for this error is that `-run` is not available in tcc.exe that is x64 (or maybe the libtcc.dll itself)  
Using x32 Dflags to compile tcc.exe seems to allow `-run` flags.  

## 2021-02-07
https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c/2029117#2029117  
https://www.studymite.com/blog/strings-in-c
https://c-for-dummies.com/blog/?p=1112  

## 2021-02-01
https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c/2029227#2029227  
https://stackoverflow.com/questions/41210227/fastest-way-to-write-integer-to-file-in-c  


## 2020-12-31
#### ArgumentsLoop study
```
// compile --compiler "Switchargument" argument
// command --parameter "subargument" "subargument" --parameter "subargument" CommandArgument
// program --parameter "subargument" "subargument" --parameter "subargument" ProgramArgument

```

https://unix.stackexchange.com/questions/285575/whats-the-difference-between-a-flag-an-option-and-an-argument

### Switches?

## 2020-12-30
#### https://www.quora.com/Is-1-true-and-0-false-in-programming
https://stackoverflow.com/questions/595450/why-does-strcmp-return-0-when-its-inputs-are-equal

```
// Most of the functions in standard C library, a successful function - returns 0 (in traditional sense - false) 
// When used directly in the If statement, this triggers Else statement.
// Therefore if (function(argument) != 0){} is often used to reverse the trend.

// Example: a string comparison
if (strcmp("test", "tests") != 0){ printf("yes");} else { printf("test");}
```
## 2020-12-22
#### Tick C Resources
https://pdos.csail.mit.edu/archive/tickc/  
https://pdos.csail.mit.edu/papers/tickc-poletto-phd.pdf  

## 2020-12-16
### Multiline Win32 Edit Control
https://docs.microsoft.com/en-us/windows/win32/controls/use-a-multiline-edit-control
### Win32 Rich Edit Control
https://docs.microsoft.com/en-us/windows/win32/controls/about-rich-edit-controls
### Compile GTK2 GTK3 Applications on Windows using GCC (and maybe adaptable for TCC)
https://stackoverflow.com/questions/56784001/how-to-build-a-gtk3-program-on-windows-without-msys2

## 2020-12-14
### Win32 AppendMenu MF_POPUP identification Issue in the WindowProcedure
https://stackoverflow.com/questions/65286191/how-to-identify-appendmenu-mf-popup-menu-in-the-windowprocedure
#### Icon Handlers
https://docs.microsoft.com/en-us/windows/win32/shell/how-to-create-icon-handlers
#### Process creation without a Window
https://stackoverflow.com/questions/13954537/c-windows-createchildprocess-hide-do-not-show-the-child-process-console-win
#### Manipulation of Desktop Icons
https://stackoverflow.com/questions/49964260/manipulating-the-positions-of-desktop-icons/49964613#49964613

## 2020-12-12
### Thread on embeding an icon to non-executable
https://docs.microsoft.com/en-us/answers/questions/193982/linking-and-embedding-icon-for-a-non-executable-fi.html

## 2020-12-10
### Research on Windows Resource Icons and general icons - filetype icons
https://superuser.com/questions/764643/how-can-i-give-a-file-a-custom-icon

## 2020-12-09
### Win32 Research on injection into running CMD process to change Environment Block
https://social.msdn.microsoft.com/Forums/en-US/db75e7c3-3c86-4fa7-a12c-8b3ad454bc99/how-to-write-win32-winapi-hack-program-in-c-language-that-prints-something-on-cmdexe-console?forum=vcgeneral  
https://stackoverflow.com/questions/54121245/how-to-execute-commands-from-an-attached-console

## 2020-12-08
### Research on windres to add icons resource to the executable
https://lists.nongnu.org/archive/html/tinycc-devel/2014-02/msg00049.html  
https://en.wikibooks.org/wiki/Windows_Programming/Resource_Script_Reference  
https://www.google.com/search?ei=8K3PX5iHEMSxrgSzmbaQDg&q=win32+resource++paper&oq=win32+resource++paper&gs_lcp=CgZwc3ktYWIQA1CgbVj0dWC5fGgAcAB4AIABigGIAe4IkgEDOC40mAEAoAEBqgEHZ3dzLXdpesABAQ&sclient=psy-ab&ved=0ahUKEwiYv93-6r7tAhXEmIsKHbOMDeIQ4dUDCA0&uact=5  
https://www.codeguru.com/cpp/w-p/win32/tutorials/article.php/c12873/Hacking-Icon-Resources.htm

## 2020-12-07
### windres to add icons resource to the executable
The main source for learning C programming language so far.
https://stackoverflow.com/questions/708238/how-do-i-add-an-icon-to-a-mingw-gcc-compiled-executable/708382#708382

## 2020-11-25
### C: A Reference Manual, 5th Edition 5th Edition
The main source for learning C programming language so far.

## 2020-11-21
### Integrate Tiny C Compiler with Run As in Windows 10
https://www.google.com/search?sxsrf=ALeKk03OOzMxgcN9HJbX96jVl27a9NPoDw%3A1605970685609&ei=_Sq5X4LNJImxrgTlyIbQDA&q=file+association+set+add+change+registry+win32&oq=file+association+set+add+change+registry+win32&gs_lcp=CgZwc3ktYWIQAzoECAAQRzoECCMQJ1D04gZYuesGYOnvBmgAcAJ4AIABjgGIAaUGkgEDNC40mAEAoAEBqgEHZ3dzLXdpesgBCMABAQ&sclient=psy-ab&ved=0ahUKEwjCv_CB85PtAhWJmIsKHWWkAcoQ4dUDCA0&uact=5

https://docs.microsoft.com/en-us/windows/win32/shell/fa-sample-scenarios

https://stackoverflow.com/questions/2681878/associate-file-extension-with-application/2697804#2697804

In .lnk file as target:
```
%windir%\system32\cmd.exe /c "tcc.exe -run"
```
shorcoming: .lnk files Not working with Run As.

In Batch file 
```
@ECHO OFF
%windir%\system32\cmd.exe /c "tcc.exe -run %1"
echo.
pause
```

## 2020-11-12
### C language referencing manual
https://www.quora.com/What-is-the-best-reference-for-the-C-programming-language/answer/Dave-Hansen-4
**C and tcc: A Language and Compiler for Dynamic Code Generation**  
http://web.stanford.edu/~engler/tickc.pdf
**Harbison and Steele’s C: A Reference Manual fifth edition**
**Compiler Design in C** by ALLEN HOLUB  
https://holub.com/compiler/  

## 2020-10-13
### C language specification standard
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf  
https://www.google.com/search?q=c99+standard&oq=c99+sta&aqs=chrome.0.0i20i263i457j69i57j0i67j0i20i263j0i67l2j0j69i61.2855j0j7&sourceid=chrome&ie=UTF-8  

### Native win32 to download a file
http://www.plugincafe.com/forum/forum_posts.asp?TID=10627&PID=41265#41265
https://docs.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/ms775123(v=vs.85)



---
## 2020-05-04

## Digital Mars Compiler Manual Setup on Windows Environment
1. Download ` Digital Mars C/C++ Compiler Version 8.57 (3662658 bytes) (NEW!)`
  * https://digitalmars.com/download/freecompiler.html
2. Extract and use command prompt to go to the extraction directory
3. Create a simple text file with Hello World example in C language. (filename: helloWorld.c)
4. Execute compilation via `dmc` Digital Mars Compiler
   ```
   
   D:\dm\bin>dmc test.c
   link test,,,user32+kernel32/noi;
   
   
   ```



## GCC compiler Manual Setup on Windows Environment
http://www.mingw.org/wiki/HOWTO_Install_the_MinGW_GCC_Compiler_Suite#toc1  
http://winlibs.com/  
https://github.com/brechtsanders/winlibs_mingw  


### Hello World Example in C language
```
#include <stdio.h>
int main() {
   // printf() displays the string inside quotation
   printf("Hello, World!");
   return 0;
}
```



### In Linux
```
sudo apt install gcc
sudo apt-get install libgtk-3-dev

```

## example-0.c

```
#include <gtk/gtk.h>

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
```


## compile

```
gcc `pkg-config --cflags gtk+-3.0` -o example-0 example-0.c `pkg-config --libs gtk+-3.0`
```
