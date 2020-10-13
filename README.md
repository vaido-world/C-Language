# C-Language-Tutorial

## 2020-10-13
### C language specification standard
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf  
https://www.google.com/search?q=c99+standard&oq=c99+sta&aqs=chrome.0.0i20i263i457j69i57j0i67j0i20i263j0i67l2j0j69i61.2855j0j7&sourceid=chrome&ie=UTF-8  




---


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
