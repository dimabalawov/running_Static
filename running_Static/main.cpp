#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"
#include <string> 
#include <iostream> 
#include <ctime>
using namespace std;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic;
HINSTANCE hInst;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
void GetStaticCoordinates(HWND hWndStatic, RECT& rect)
{
    GetWindowRect(hWndStatic, &rect);
    HWND hParent = GetParent(hWndStatic);

    POINT topLeft = { rect.left, rect.top };
    POINT bottomRight = { rect.right, rect.bottom };

    ScreenToClient(hParent, &topLeft);
    ScreenToClient(hParent, &bottomRight);

    rect.left = topLeft.x;
    rect.top = topLeft.y;
    rect.right = bottomRight.x;
    rect.bottom = bottomRight.y;
}
BOOL IsCursorOverStatic(HWND hWnd)
{
    POINT pt;
    RECT rect;
    GetCursorPos(&pt);
    GetWindowRect(hWnd, &rect);
    return PtInRect(&rect, pt);
}
VOID MoveStatic(HWND hWnd)
{
    srand(time(0));
    int randPos = rand() % 3;
    RECT rect;
    GetStaticCoordinates(hWnd, rect);
    if (rect.left == 0 && rect.top == 0)
    {
        switch (randPos)
        {
        case 0:
            MoveWindow(hWnd, 600, 390, 150, 150, TRUE);
            break;
        case 1:
            MoveWindow(hWnd, 0, 390, 150, 150, TRUE);
            break;
        case 2:
            MoveWindow(hWnd, 600, 0, 150, 150, TRUE);
            break;
        }
    }
    else if (rect.left == 600 && rect.top == 390)
    {
        switch (randPos)
        {
        case 0:
            MoveWindow(hWnd, 0, 0, 150, 150, TRUE);
            break;
        case 1:
            MoveWindow(hWnd, 0, 390, 150, 150, TRUE);
            break;
        case 2:
            MoveWindow(hWnd, 600, 0, 150, 150, TRUE);
            break;
        }
    }
    else if (rect.left == 0 && rect.top == 390)
    {
        switch (randPos)
        {
        case 0:
            MoveWindow(hWnd, 0, 0, 150, 150, TRUE);
            break;
        case 1:
            MoveWindow(hWnd, 600, 390, 150, 150, TRUE);
            break;
        case 2:
            MoveWindow(hWnd, 600, 0, 150, 150, TRUE);
            break;
        }
    }
    else
    {
        switch (randPos)
        {
        case 0:
            MoveWindow(hWnd, 0, 0, 150, 150, TRUE);
            break;
        case 1:
            MoveWindow(hWnd, 600, 390, 150, 150, TRUE);
            break;
        case 2:
            MoveWindow(hWnd, 0, 390, 150, 150, TRUE);
            break;
        }
    }
}
INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{

    switch (message)
    {
    case WM_INITDIALOG:
        hStatic = CreateWindowEx(0, TEXT("STATIC"), 0,
            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
            0, 0, 150, 150, hWnd, 0, hInst, 0);
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    case WM_MOUSEMOVE:
        if (IsCursorOverStatic(hStatic))
        {
            MoveStatic(hStatic);
        }
        return TRUE;
    }
    return FALSE;
}
