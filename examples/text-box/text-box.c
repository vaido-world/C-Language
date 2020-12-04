#include <windows.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR nCmdLine, int nCmdShow)
{
  LPTSTR windowClass = TEXT("WinApp");
  LPTSTR windowTitle = TEXT("Windows Application");
  WNDCLASSEX wcex;

  wcex.cbClsExtra = 0;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.cbWndExtra = 0;
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hInstance = hInstance;
  wcex.lpfnWndProc = WndProc;
  wcex.lpszClassName = windowClass;
  wcex.lpszMenuName = NULL;
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL, TEXT("RegisterClassEx Failed!"), TEXT("Error"),
               MB_ICONERROR);
    return 1;
  }

  HWND hWnd;

  if (!(hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                            CW_USEDEFAULT, NULL, NULL, hInstance, NULL)))
  {
    MessageBox(NULL, TEXT("CreateWindow Failed!"), TEXT("Error"), MB_ICONERROR);
    return 1;
  }

  HWND hWndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
                               WS_CHILD | WS_VISIBLE, 100, 20, 140,
                               20, hWnd, NULL, NULL, NULL);

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg;

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
  default:
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }
  return FALSE;
}