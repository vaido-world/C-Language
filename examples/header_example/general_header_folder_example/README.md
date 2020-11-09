In this example we use general header folder.  
The main.c file will be changed to look for header file in the `headers` folder.  
Although to generate the object file, it is still needed for `myfun.c` to be compiled along the `main.c`  


[`main.c`](https://github.com/vaido-world/C-Language-Tutorial/blob/6b60c26f21cc12c1664be7c032d7f872a568454c/examples/header_example/general_header_folder_example/main.c#L1-L5)

```
#include <stdio.h>
#include "headers\myfun.h"
 
int main()
{
```

