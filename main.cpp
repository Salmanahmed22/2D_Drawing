#include <bits/stdc++.h>
#include "Algorithms.h"
using namespace std;
// Global Data
vector<POINT> points;
HBRUSH hBackgroundBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
HCURSOR hCurrentCursor = LoadCursor(NULL, IDC_ARROW);


// Menu Command IDs
#define IDM_BG_WHITE          1
#define IDM_BG_BLACK          2
#define IDM_CURSOR_ARROW      3
#define IDM_CURSOR_CROSS      4
#define IDM_SAVE              5
#define IDM_LOAD              6

// Shape Algorithms
#define IDM_LINE_DDA          100
#define IDM_LINE_MIDPOINT     101
#define IDM_LINE_PARAMETRIC   102
#define IDM_CIRCLE_DIRECT     103
#define IDM_CIRCLE_POLAR      104
#define IDM_CIRCLE_ITER_POLAR 105
#define IDM_CIRCLE_MIDPOINT   106
#define IDM_CIRCLE_MOD_MID    107

#define IDM_FILL_CIRCLE_LINES 108
#define IDM_FILL_CIRCLE_CIRC  109
#define IDM_FILL_SQUARE_HERM  110
#define IDM_FILL_RECT_BEZIER  111
#define IDM_FILL_CONVEX       112
#define IDM_FILL_NONCONVEX    113
#define IDM_FLOOD_RECURSIVE   114
#define IDM_FLOOD_NONREC      115
#define IDM_CARDINAL_SPLINE   116
#define IDM_ELLIPSE_DIRECT    117
#define IDM_ELLIPSE_POLAR     118
#define IDM_ELLIPSE_MIDPOINT  119
#define IDM_CLIP_RECT_POINT   120
#define IDM_CLIP_RECT_LINE    121
#define IDM_CLIP_RECT_POLY    122
#define IDM_CLIP_SQUARE_POINT 123
#define IDM_CLIP_SQUARE_LINE  124

// Function declarations
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void SetupMenus(HWND hwnd);

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

    SetupMenus(hwnd);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void SetupMenus(HWND hwnd) {
    HMENU hMenuBar = CreateMenu();
    HMENU hOptions = CreatePopupMenu();
    HMENU hShapes = CreatePopupMenu();
    HMENU hFilling = CreatePopupMenu();
    HMENU hClipping = CreatePopupMenu();

    // Submenus for shapes
    HMENU hLines = CreatePopupMenu();
    AppendMenu(hLines, MF_STRING, IDM_LINE_DDA, "DDA");
    AppendMenu(hLines, MF_STRING, IDM_LINE_MIDPOINT, "Midpoint");
    AppendMenu(hLines, MF_STRING, IDM_LINE_PARAMETRIC, "Parametric");

    HMENU hCircles = CreatePopupMenu();
    AppendMenu(hCircles, MF_STRING, IDM_CIRCLE_DIRECT, "Direct");
    AppendMenu(hCircles, MF_STRING, IDM_CIRCLE_POLAR, "Polar");
    AppendMenu(hCircles, MF_STRING, IDM_CIRCLE_ITER_POLAR, "Iterative Polar");
    AppendMenu(hCircles, MF_STRING, IDM_CIRCLE_MIDPOINT, "Midpoint");
    AppendMenu(hCircles, MF_STRING, IDM_CIRCLE_MOD_MID, "Modified Midpoint");

    HMENU hEllipses = CreatePopupMenu();
    AppendMenu(hEllipses, MF_STRING, IDM_ELLIPSE_DIRECT, "Direct");
    AppendMenu(hEllipses, MF_STRING, IDM_ELLIPSE_POLAR, "Polar");
    AppendMenu(hEllipses, MF_STRING, IDM_ELLIPSE_MIDPOINT, "Midpoint");

    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hLines, "Lines");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hCircles, "Circles");
    AppendMenu(hShapes, MF_POPUP, (UINT_PTR)hEllipses, "Ellipses");
    AppendMenu(hShapes, MF_STRING, IDM_CARDINAL_SPLINE, "Cardinal Spline");

    // Submenus for Filling
    HMENU hFillCircle = CreatePopupMenu();
    AppendMenu(hFillCircle, MF_STRING, IDM_FILL_CIRCLE_LINES, "With Lines");
    AppendMenu(hFillCircle, MF_STRING, IDM_FILL_CIRCLE_CIRC, "With Circles");

    HMENU hFillPolygon = CreatePopupMenu();
    AppendMenu(hFillPolygon, MF_STRING, IDM_FILL_CONVEX, "Convex");
    AppendMenu(hFillPolygon, MF_STRING, IDM_FILL_NONCONVEX, "Non-Convex");

    HMENU hFloodFill = CreatePopupMenu();
    AppendMenu(hFloodFill, MF_STRING, IDM_FLOOD_RECURSIVE, "Recursive");
    AppendMenu(hFloodFill, MF_STRING, IDM_FLOOD_NONREC, "Non-Recursive");

    AppendMenu(hFilling, MF_POPUP, (UINT_PTR)hFillCircle, "Fill Circle");
    AppendMenu(hFilling, MF_STRING, IDM_FILL_SQUARE_HERM, "Fill Square (Hermite)");
    AppendMenu(hFilling, MF_STRING, IDM_FILL_RECT_BEZIER, "Fill Rectangle (Bezier)");
    AppendMenu(hFilling, MF_POPUP, (UINT_PTR)hFillPolygon, "Fill Polygon");
    AppendMenu(hFilling, MF_POPUP, (UINT_PTR)hFloodFill, "Flood Filling");

    // Submenus for Clipping
    HMENU hClipRect = CreatePopupMenu();
    AppendMenu(hClipRect, MF_STRING, IDM_CLIP_RECT_POINT, "Point");
    AppendMenu(hClipRect, MF_STRING, IDM_CLIP_RECT_LINE, "Line");
    AppendMenu(hClipRect, MF_STRING, IDM_CLIP_RECT_POLY, "Polygon");

    HMENU hClipSquare = CreatePopupMenu();
    AppendMenu(hClipSquare, MF_STRING, IDM_CLIP_SQUARE_POINT, "Point");
    AppendMenu(hClipSquare, MF_STRING, IDM_CLIP_SQUARE_LINE, "Line");

    AppendMenu(hClipping, MF_POPUP, (UINT_PTR)hClipRect, "Rectangle");
    AppendMenu(hClipping, MF_POPUP, (UINT_PTR)hClipSquare, "Square");

    // Options Menu
    HMENU hBackgroundColor = CreatePopupMenu();
    AppendMenu(hBackgroundColor, MF_STRING, IDM_BG_WHITE, "White");
    AppendMenu(hBackgroundColor, MF_STRING, IDM_BG_BLACK, "Black");

    HMENU hCursor = CreatePopupMenu();
    AppendMenu(hCursor, MF_STRING, IDM_CURSOR_ARROW, "Arrow");
    AppendMenu(hCursor, MF_STRING, IDM_CURSOR_CROSS, "Cross");

    AppendMenu(hOptions, MF_POPUP, (UINT_PTR)hBackgroundColor, "Background");
    AppendMenu(hOptions, MF_POPUP, (UINT_PTR)hCursor, "Cursor");
    AppendMenu(hOptions, MF_STRING, IDM_SAVE, "Save");
    AppendMenu(hOptions, MF_STRING, IDM_LOAD, "Load");

    // Final Menu Bar
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hOptions, "Options");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hShapes, "Shapes");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFilling, "Filling");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hClipping, "Clipping");

    SetMenu(hwnd, hMenuBar);
}


// WndProc (Placeholder for now)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    static int currentOption = 0;
    static int xc, yc;
    switch (msg) {
        case WM_COMMAND: {
            switch (LOWORD(wp)) {
                case IDM_BG_WHITE:{
                    hBackgroundBrush = (HBRUSH) GetStockObject(WHITE_BRUSH);
                    InvalidateRect(hwnd, nullptr, TRUE);
                    break;
                }
                case IDM_BG_BLACK: {
                    hBackgroundBrush = (HBRUSH) GetStockObject(BLACK_BRUSH);
                    InvalidateRect(hwnd, nullptr, TRUE);
                    break;
                }
                case IDM_CURSOR_ARROW: {
                    hCurrentCursor = LoadCursor(nullptr, IDC_ARROW);
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR) hCurrentCursor);
                    SetCursor(hCurrentCursor);
                    break;
                }
                case IDM_CURSOR_CROSS: {
                    hCurrentCursor = LoadCursor(nullptr, IDC_CROSS);
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR) hCurrentCursor);
                    SetCursor(hCurrentCursor);
                    break;
                }
                case IDM_SAVE:       // TODO: Implement Save
                case IDM_LOAD:       // TODO: Implement Load
                case IDM_LINE_DDA:   // TODO: Implement DDA Line
                case IDM_LINE_MIDPOINT:
                case IDM_LINE_PARAMETRIC:{
                    currentOption = IDM_LINE_PARAMETRIC;
                    break;
                }
                case IDM_CIRCLE_DIRECT:
                case IDM_CIRCLE_POLAR:
                case IDM_CIRCLE_ITER_POLAR:
                case IDM_CIRCLE_MIDPOINT:
                case IDM_CIRCLE_MOD_MID: {
                    currentOption = IDM_CIRCLE_MOD_MID;
                    break;
                }
                case IDM_FILL_CIRCLE_LINES:
                case IDM_FILL_CIRCLE_CIRC:
                case IDM_FILL_SQUARE_HERM:
                case IDM_FILL_RECT_BEZIER:
                case IDM_FILL_CONVEX:
                case IDM_FILL_NONCONVEX:
                case IDM_FLOOD_RECURSIVE:
                case IDM_FLOOD_NONREC:
                case IDM_CARDINAL_SPLINE:
                case IDM_ELLIPSE_DIRECT:
                case IDM_ELLIPSE_POLAR:
                case IDM_ELLIPSE_MIDPOINT:
                case IDM_CLIP_RECT_POINT:
                case IDM_CLIP_RECT_LINE:
                case IDM_CLIP_RECT_POLY:
                case IDM_CLIP_SQUARE_POINT:
                case IDM_CLIP_SQUARE_LINE:
                    MessageBox(hwnd, "Functionality not implemented yet!", "TODO", MB_OK);
                    break;
            }
            break;
        }
        case WM_LBUTTONDOWN:{
            switch (currentOption) {
                case IDM_CIRCLE_DIRECT:
                case IDM_CIRCLE_POLAR:
                case IDM_CIRCLE_ITER_POLAR:
                case IDM_CIRCLE_MIDPOINT:
                case IDM_CIRCLE_MOD_MID:{
                    xc = LOWORD(lp);
                    yc = HIWORD(lp);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case WM_LBUTTONUP:{
            switch (currentOption) {
                case IDM_CIRCLE_DIRECT:
                case IDM_CIRCLE_POLAR:
                case IDM_CIRCLE_ITER_POLAR:
                case IDM_CIRCLE_MIDPOINT:
                case IDM_CIRCLE_MOD_MID:{
                    hdc = GetDC(hwnd);
                    int x, y, r;
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    r = static_cast<int>(sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc)));
                    switch (currentOption) {
                        case IDM_CIRCLE_DIRECT:
                        case IDM_CIRCLE_POLAR:
                        case IDM_CIRCLE_ITER_POLAR:
                        case IDM_CIRCLE_MIDPOINT:
                        case IDM_CIRCLE_MOD_MID:{
                            DrawCircleModifiedMidpoint(hdc, xc, yc, r, RGB(0, 0, 255));
                            break;
                        }
                        default:
                            break;
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                }
                default:
                    break;
            }
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
