/* WindowHandle.c
	Register the Window Class
	Create the Window Handle
	Use the Window Handle
	Run Message Loop
	Call WindowProc

Resources:
	https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
	https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues
____________________________________________________________________________________________*/

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

//___________________________Function Declarations_________________________________

LRESULT 
CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//____________________________The Main Program_____________________________________

int 
WINAPI wWinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		PWSTR       pCmdLine, 
		int         nCmdShow)
{
//____________________________Register_the_window_class____________________________
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	
	WNDCLASS WindowClass = { };
	WindowClass.lpfnWndProc   = WindowProc;
	WindowClass.hInstance     = hInstance;
	WindowClass.lpszClassName = CLASS_NAME;
	RegisterClass(&WindowClass);

//____________________________C̲r̲e̲a̲t̲e̲_t̲h̲e̲_W̲i̲n̲d̲o̲w̲_H̲a̲n̲d̲l̲e̲̲_____________________________
	DWORD dwExStyle;
	LPTSTR lpClassName;
	LPTSTR lpWindowName;
	int dwStyle;
	int	X;
	int	Y;
	int nWidth;
	int	nHeight;
	
	HWND      hWndParent;
	HMENU     hMenu;
	LPVOID    lpParam;
	
	HWND WindowHandle = CreateWindowEx(
		(DWORD)  dwExStyle        = 0,                                   // Optional window styles.
		(LPTSTR) lpClassName      = (LPTSTR)WindowClass.lpszClassName,   // Window class
		(LPTSTR) lpWindowName     = L"Learn to Program Windows",         // Window text
		(int)    dwStyle          = WS_OVERLAPPEDWINDOW,                 // Window style

		// Size and position
		(int) X         = CW_USEDEFAULT, 
		(int) Y         = CW_USEDEFAULT, 
		(int) nWidth    = CW_USEDEFAULT, 
		(int) nHeight   = CW_USEDEFAULT,

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

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
} 
//____________________________The End of the Program________________________________
 

//____________________________WindowProc callback function___________________________
// Window Procedure, react to changes in the Window.
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

LRESULT 
CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);



			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

			EndPaint(hwnd, &ps);
			}
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
