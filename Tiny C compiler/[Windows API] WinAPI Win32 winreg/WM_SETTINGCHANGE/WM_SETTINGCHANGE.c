#pragma comment(lib, "user32")
#include <windows.h> // includes also: winuser.h


// https://stackoverflow.com/questions/4968373/why-doesnt-sendmessagetimeout-update-the-environment-variables/7547964#7547964
// https://stackoverflow.com/questions/573817/where-are-environment-variables-stored-in-registry/573818#573818
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessagetimeouta

// only works after closing all Command line windows and reopening new one 
void main(){
SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) "Environment", SMTO_ABORTIFHUNG, 1000, NULL );
SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) L"Environment", SMTO_ABORTIFHUNG, 1000, NULL );	
//	
//		HWND       hWnd       = HWND_BROADCAST;
//		UINT       Msg        = WM_SETTINGCHANGE;
//		WPARAM     wParam     = 0;
//		LPARAM     lParam     = (LPARAM) L"Environment";
//		UINT       fuFlags    = SMTO_ABORTIFHUNG;
//		UINT       uTimeout   = 0;
//		PDWORD_PTR lpdwResult = NULL;
//	
//	
//	
//	SendMessageTimeoutA(
//		hWnd,
//		Msg,	
//		wParam,	
//		lParam,	
//		fuFlags,	
//		uTimeout,	
//		lpdwResult	
//	);
	
}
