#include <windows.h>

//___________________________Function Declarations_________________________________
void addMenus();


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
			
			// Loading an Icon
			HICON hIcon; 
			hIcon = LoadIcon(NULL, IDI_QUESTION); 
			
			// Taskbar Icon
			SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			
			// Window Icon
			SendMessage (hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			
			// Client area Icon
			DrawIconEx( hdc,    // Handle for Device Context
				100,        // xLeft
				200,        // yTop
				hIcon,      // hIcon
				72,         // cxWidth
				78,         // cyWidth
				0,          // istepIfAniCur
				NULL,       // hbrFlickerFreeDraw
				DI_NORMAL); // diFlags

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
