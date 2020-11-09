#include <windows.h>
#ifndef A_VARIABLES_H
#define A_VARIABLES_H

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

        // ----------------------- first and last
        case WM_CREATE:
            CenterWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        // ----------------------- get out of it...
        case WM_RBUTTONUP:
            DestroyWindow(hwnd);
            break;

        case WM_KEYDOWN:
            if (VK_ESCAPE == wParam)
                DestroyWindow(hwnd);
            break;

        // ----------------------- display our minimal info
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC         hdc;
            RECT        rc;
            hdc = BeginPaint(hwnd, &ps);

            GetClientRect(hwnd, &rc);
            SetTextColor(hdc, RGB(240,240,96));
            SetBkMode(hdc, TRANSPARENT);
            DrawText(hdc, pWindowText, -1, &rc, DT_CENTER|DT_SINGLELINE|DT_VCENTER);

            EndPaint(hwnd, &ps);
            break;
        }

        // ----------------------- let windows do all other stuff
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

#endif