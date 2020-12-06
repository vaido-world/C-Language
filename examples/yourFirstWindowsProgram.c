#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
//https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
LRESULT 
CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int 
WINAPI wWinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		PWSTR		pCmdLine, 
		int			nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	
	WNDCLASS wc = { };
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	// Create the window.
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
	
	HWND hwnd = CreateWindowEx(
		(DWORD)  dwExStyle        = 0,                                   // Optional window styles.
		(LPTSTR) lpClassName      = (LPTSTR)wc.lpszClassName,            // Window class
		(LPTSTR) lpWindowName     = L"Learn to Program Windows",         // Window text
		(int)    dwStyle          = WS_OVERLAPPEDWINDOW,                 // Window style

		// Size and position
		(int) X 		= CW_USEDEFAULT, 
		(int) Y 		= CW_USEDEFAULT, 
		(int) nWidth 	= CW_USEDEFAULT, 
		(int) nHeight	= CW_USEDEFAULT,

		(HWND)      hWndParent = NULL,		// Parent window    
		(HMENU)     hMenu      = NULL,		// Menu
		(HINSTANCE) hInstance  = hInstance,	// Instance handle
		(LPVOID)    lpParam    = NULL		// Additional application data
		);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
