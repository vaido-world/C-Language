## Compilers

**cl.exe** is distributed via [**V**isual **S**tudio Build Tools.](https://visualstudio.microsoft.com/downloads/)  
**gcc.exe** is distributed by [**Min**imalist **G**NU for **W**indows.](http://www.mingw.org/)  
**tcc.exe** is distributed by [GNU Savannah project ](http://savannah.gnu.org/projects/tinycc)   

By default GNU C Compiler is preferred for compiling TCC compiler.



The **build-tcc.cmd** script is meant to compile Tiny C Compiler.

1. There is no need for other compilers if you already have a Tiny C Compiler.  
   Add the tcc folder to the Path Environment Variable and launch **build-tcc.cmd**

2. **gcc.exe** and **cl.exe** compilers are only used to produce **tcc.exe** binary.  
   TCC Libraries are always compiled by the **tcc.exe** compiler itself.

It takes gcc or cl compiler and 

The script itself try to search for compilers and 

