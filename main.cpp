#include <bits/stdc++.h>
#include "Include/Var&defines.h"
#include "Include/MenuController.h"
using namespace std;

HBRUSH hBackgroundBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
HCURSOR hCurrentCursor = LoadCursor(NULL, IDC_ARROW);


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpszClassName = "DrawingApp";
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;

    if (!RegisterClass(&wc)) return -1;

    HWND hwnd = CreateWindow("DrawingApp", "2D Drawing Program",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             800, 600, NULL, NULL, hInstance, NULL);
    if (!hwnd) return -1;

    HMENU hMenuBar = SetupMenus();
    SetMenu(hwnd, hMenuBar);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc = nullptr;
    switch (msg) {
        case WM_COMMAND: {
            HandleChoice(hBackgroundBrush, hCurrentCursor, hwnd, wp, lp, hdc, vars);
            break;
        }
        case WM_LBUTTONDOWN:{
            HandleLeftButtonDOWN(hwnd, wp, lp, hdc, vars);
            break;
        }
        case WM_LBUTTONUP:{
            HandleLeftButtonUP(hwnd, wp, lp, hdc, vars);
            break;
        }
        case WM_ERASEBKGND: {
            hdc = (HDC)wp;
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, hBackgroundBrush);
            return 1;
        }
        case WM_SETCURSOR: {
            SetCursor(hCurrentCursor);
            return TRUE;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default: {
            return DefWindowProc(hwnd, msg, wp, lp);
        }
    }
    return 0;
}
