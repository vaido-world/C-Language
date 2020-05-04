# C-Language-Tutorial


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
