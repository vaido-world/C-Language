# C-Language-Tutorial

## 2021-07-16
### Program
```
#ifndef NOT_TESTING
#define NOT_TESTING
void Program2_libfunc(); // program.c:6: warning: implicit declaration of function 'libfunc'
                // Program2.c:12: error: incompatible types for redefinition of 'libfunc'
int main() {
	printf("Program1\n");
	Program2_libfunc();
}
#endif

// Triggers implicit declaration of the function
#ifndef PROGRAM2_C
#define PROGRAM2_C
#include "Program2.c"
#endif /* PROGRAM2_C */
```

### Program2
```
#ifndef NOT_TESTING
#define NOT_TESTING
void Program2_libfunc(); // program2.c:6: warning: implicit declaration of function 'libfunc'
                // Program2.c:12: error: incompatible types for redefinition of 'libfunc'
int main() {
	printf("Program2\n");
	Program2_libfunc();
}
#endif

#ifndef LIBFUNC_C
#define LIBFUNC_C
void Program2_libfunc(){
	printf(" This is libfunc\n");
}
#endif /* LIBFUNC_C */

#ifndef PROGRAM1_C
#define PROGRAM1_C
#include "Program.c"
#endif /* PROGRAM1_C */
```

## 2021-07-11
https://www.google.lt/url?sa=t&source=web&rct=j&url=https://solidsands.com/wp-content/uploads/Master_Thesis_Vasileios_GemistosFinal.pdf&ved=2ahUKEwilxLOA_NrxAhWwxIsKHW1BD0I4FBAWMAN6BAgBEAI&usg=AOvVaw2L3vjh_8Ojg0pPD5R19ab6

## 2021-06-20
Tiny C Compiler Community Examples: `tcc/examples/community` or `tcc/community_examples` or `community_resources`  
Internet Connection, HTTP    
Registry Access  

## 2021-06-03
https://stackoverflow.com/questions/20055838/hello-world-with-tcc-using-assembly-language/20075715#20075715

## 2021-06-02
https://elmicro.com/files/cosmic/clanguage.pdf

## 2021-06-01
### Looking at the C language compiler output using -E Preprocesor parameter in TCC
`tcc -E  windowproc.c`

```
#define main __FILE__ 
void main() 
{ 
	printf("WindowProc\n");
	gets();

} 
```

Output of `tcc -E  windowproc.c`

```

void "windowproc.c"()
{
        printf("WindowProc\n");
        gets();

}

```
**Notice:** As can be seen `__FILE__` is expanded to `"windowproc.c"` the quotes (`""`) seem to not let to use this macro as function name. 

### Some average quality C Reference Book
c language reference book manual c89
http://www.cs.columbia.edu/~sedwards/papers/sgi1999c.pdf
### References
https://www.tutorialspoint.com/c_standard_library/index.htm  
https://www.tutorialspoint.com/cprogramming/index.htm

### Redefining main method with Macros (Use macro as function name)

`__FILE__` macro is not expanded in the function name.
#### Example: WindowProc.c
```
#ifndef __FILE__t
#define __FILE__t main
#endif

void __FILE__t() 
{ 
	printf("WindowProc\n");
	gets();

} 
```

It is simply treated as function name `__FILE__t` instead of `WindowProc.c_t`

### Redefining main method with literal strings
As mentioned function names do not expand macros and are treated directly as literal strings.
#### Example: 
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
