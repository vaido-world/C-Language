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

//___________________________Function Declarations_________________________________

LRESULT 
CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void addMenus(HWND);

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
 

//____________________________WindowProcedure callback function___________________________
// Window Procedure, react to changes in the Window.
// DispatchMessage() is calling the WindowProcedure that is attached in the WindowClass as: WindowClass.lpfnWndProc
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

LRESULT 
CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) //WM_ (WindowMessage)
	{
	case WM_MENUCOMMAND:

		DestroyWindow(hwnd);
		return 0;
	case WM_COMMAND:
		switch(wParam){
			case 1:
				MessageBox(hwnd, TEXT("asd"), L"yes", MB_HELP);
				MessageBeep(MB_OK);
				return 0;
			case 3:
				DestroyWindow(hwnd);
				return 0;
		}
		return 0;
		
	case WM_CREATE:
		addMenus(hwnd);
		return 0;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_BACKGROUND+1));
			
			HICON hIcon; 
			hIcon = LoadIcon(NULL, IDI_QUESTION); 
			
			// Taskbar Icon
			SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			
			// Window Icon
			SendMessage (hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			
			// Client area Icon
			DrawIconEx( hdc, 100, 200,hIcon, 72, 78, 0, NULL, DI_NORMAL);

			EndPaint(hwnd, &ps);
			}
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void addMenus(HWND hwnd){
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	
	UINT     uFlags;
	UINT_PTR uIDNewItem;
	LPWSTR   lpNewItem;
	
	
	AppendMenu(hMenu, uFlags=MF_POPUP, uIDNewItem=(UINT_PTR)hFileMenu, lpNewItem=TEXT("File"));
		AppendMenu(hFileMenu, uFlags=MF_STRING,    uIDNewItem=1, lpNewItem=TEXT("New"));;
		AppendMenu(hFileMenu, uFlags=MF_STRING,    uIDNewItem=2, lpNewItem=TEXT("Open"));;
		AppendMenu(hFileMenu, uFlags=MF_SEPARATOR, uIDNewItem=3, lpNewItem=0);
		AppendMenu(hFileMenu, uFlags=MF_STRING,    uIDNewItem=3, lpNewItem=TEXT("Exit"));;
	AppendMenu(hMenu, uFlags=MF_STRING,            uIDNewItem=2, lpNewItem=TEXT("BoQsc"));
	SetMenu(hwnd, hMenu);
}
