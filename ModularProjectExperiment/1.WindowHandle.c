/* WindowHandle.c
	Register the Window Class
	Create the Window Handle
	Use the Window Handle
	Run Message Loop
	Call WindowProcedure

Resources:
	https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
	https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues
____________________________________________________________________________________________*/

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "2.WindowProcedure.c"

//___________________________Function Declarations_________________________________



//____________________________The Main Program_____________________________________

int 
WINAPI wWinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		PWSTR       pCmdLine, 
		int         nCmdShow)
{
//____________________________Register_the_Window_Class____________________________	
	WNDCLASS WindowClass = { };
	WindowClass.lpfnWndProc   = WindowProcedure;
	WindowClass.hInstance     = hInstance;
	WindowClass.lpszClassName = L"Sample Window Class";
	WindowClass.hCursor       = LoadCursor(NULL, IDC_ARROW); // Default Cursor. (Else, When moving mouse outside to inside client area, the cursor inside client area - depends on the outside cursor.)
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Default Background.
	RegisterClass(&WindowClass);

//____________________________C̲r̲e̲a̲t̲e̲_t̲h̲e̲_W̲i̲n̲d̲o̲w̲_H̲a̲n̲d̲l̲e̲̲_____________________________
	DWORD dwExStyle;
	LPTSTR lpClassName;
	LPTSTR lpWindowName;
	int dwStyle;
	int	X;
	int	Y;
	int	nWidth;
	int	nHeight;
	
	HWND      hWndParent;
	HMENU     hMenu;
	LPVOID    lpParam;
	
	HWND WindowHandle = CreateWindowEx(
		(DWORD)  dwExStyle        = 0,                                   // Optional window style.
		(LPTSTR) lpClassName      = (LPTSTR)WindowClass.lpszClassName,   // Window class
		(LPTSTR) lpWindowName     = L"Learn to Program Windows",         // Window title
		(int)    dwStyle          = WS_OVERLAPPEDWINDOW,                 // Window style

		// Size and position
		(int) X         = CW_USEDEFAULT,    // The initial horizontal position of the window. 
		(int) Y         = CW_USEDEFAULT,    // The initial vertical position of the window. 
		(int) nWidth    = CW_USEDEFAULT,    // The width, in device units, of the window. 
		(int) nHeight   = CW_USEDEFAULT,    // The height, in device units, of the window. 

		(HWND)      hWndParent = NULL,      // Parent window    
		(HMENU)     hMenu      = NULL,      // Menu
		(HINSTANCE) hInstance  = hInstance, // Instance handle
		(LPVOID)    lpParam    = NULL       // Additional application data
		);

	if (WindowHandle == NULL)
	{
		return 0;
	}
//____________________________Use the Window Handle.________________________________

	ShowWindow(WindowHandle, nCmdShow);

//____________________________Run the Message Loop._________________________________ 
// After ShowWindow, Message Loop waits for Messages and is responsible for destruction of the Window.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // Translates virtual-key messages into character messages.
		DispatchMessage(&msg);  // Dispatches a message to a WindowProcedure.
	}

	return 0;
} 

//____________________________The End of the Program________________________________
 

