#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Circle.h"
#include "../Include/Var&defines.h"
using namespace std;

HMENU SetupMenus() {
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

    HMENU hColors = CreatePopupMenu();
    AppendMenu(hColors, MF_STRING, IDM_COLOR_RED,    "Red");
    AppendMenu(hColors, MF_STRING, IDM_COLOR_ORANGE, "Orange");
    AppendMenu(hColors, MF_STRING, IDM_COLOR_YELLOW, "Yellow");
    AppendMenu(hColors, MF_STRING, IDM_COLOR_GREEN,  "Green");
    AppendMenu(hColors, MF_STRING, IDM_COLOR_BLUE,   "Blue");
    AppendMenu(hColors, MF_STRING, IDM_COLOR_INDIGO, "Indigo");
    AppendMenu(hColors, MF_STRING, IDM_COLOR_VIOLET, "Violet");

    AppendMenu(hOptions, MF_POPUP, (UINT_PTR)hBackgroundColor, "Background");
    AppendMenu(hOptions, MF_POPUP, (UINT_PTR)hCursor, "Cursor");
    AppendMenu(hOptions, MF_POPUP, (UINT_PTR)hColors, "Color");
    AppendMenu(hOptions, MF_STRING, IDM_SAVE, "Save");
    AppendMenu(hOptions, MF_STRING, IDM_LOAD, "Load");

    // Final Menu Bar
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hOptions, "Options");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hShapes, "Shapes");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFilling, "Filling");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hClipping, "Clipping");

    return hMenuBar;
}

void HandleChoice(HBRUSH hBackgroundBrush, HCURSOR hCurrentCursor,HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars){
    switch (LOWORD(wp)) {
        case IDM_BG_WHITE: {
            hBackgroundBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case IDM_BG_BLACK: {
            hBackgroundBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case IDM_CURSOR_ARROW: {
            hCurrentCursor = LoadCursor(nullptr, IDC_ARROW);
            SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCurrentCursor);
            SetCursor(hCurrentCursor);
            break;
        }
        case IDM_CURSOR_CROSS: {
            hCurrentCursor = LoadCursor(nullptr, IDC_CROSS);
            SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCurrentCursor);
            SetCursor(hCurrentCursor);
            break;
        }
        case IDM_COLOR_RED:    vars.c = RGB(255, 0, 0); break;
        case IDM_COLOR_ORANGE: vars.c = RGB(255, 165, 0); break;
        case IDM_COLOR_YELLOW: vars.c = RGB(255, 255, 0); break;
        case IDM_COLOR_GREEN:  vars.c = RGB(0, 128, 0); break;
        case IDM_COLOR_BLUE:   vars.c = RGB(0, 0, 255); break;
        case IDM_COLOR_INDIGO: vars.c = RGB(75, 0, 130); break;
        case IDM_COLOR_VIOLET: vars.c = RGB(238, 130, 238); break;

        case IDM_SAVE: {
            vars.currentOption = IDM_SAVE;
            break;
        }
        case IDM_LOAD: {
            vars.currentOption = IDM_LOAD;
            break;
        }

            // line Drawing
        case IDM_LINE_DDA: {
            vars.currentOption = IDM_LINE_DDA;
            break;
        }
        case IDM_LINE_MIDPOINT: {
            vars.currentOption = IDM_LINE_MIDPOINT;
            break;
        }
        case IDM_LINE_PARAMETRIC: {
            vars.currentOption = IDM_LINE_PARAMETRIC;
            break;
        }

            // Circle Drawing
        case IDM_CIRCLE_DIRECT: {
            vars.currentOption = IDM_CIRCLE_DIRECT;
            break;
        }
        case IDM_CIRCLE_POLAR: {
            vars.currentOption = IDM_CIRCLE_POLAR;
            break;
        }
        case IDM_CIRCLE_ITER_POLAR: {
            vars.currentOption = IDM_CIRCLE_ITER_POLAR;
            break;
        }
        case IDM_CIRCLE_MIDPOINT: {
            vars.currentOption = IDM_CIRCLE_MIDPOINT;
            break;
        }
        case IDM_CIRCLE_MOD_MID: {
            vars.currentOption = IDM_CIRCLE_MOD_MID;
            break;
        }

            // Filling
        case IDM_FILL_CIRCLE_LINES: {
            vars.currentOption = IDM_FILL_CIRCLE_LINES;
            break;
        }
        case IDM_FILL_CIRCLE_CIRC: {
            vars.currentOption = IDM_FILL_CIRCLE_CIRC;
            break;
        }
        case IDM_FILL_SQUARE_HERM: {
            vars.currentOption = IDM_FILL_SQUARE_HERM;
            break;
        }
        case IDM_FILL_RECT_BEZIER: {
            vars.currentOption = IDM_FILL_RECT_BEZIER;
            break;
        }
        case IDM_FILL_CONVEX: {
            vars.currentOption = IDM_FILL_CONVEX;
            break;
        }
        case IDM_FILL_NONCONVEX: {
            vars.currentOption = IDM_FILL_NONCONVEX;
            break;
        }
        case IDM_FLOOD_RECURSIVE: {
            vars.currentOption = IDM_FLOOD_RECURSIVE;
            break;
        }
        case IDM_FLOOD_NONREC: {
            vars.currentOption = IDM_FLOOD_NONREC;
            break;
        }

            // Splines and Curves
        case IDM_CARDINAL_SPLINE: {
            vars.currentOption = IDM_CARDINAL_SPLINE;
            break;
        }

            // Ellipse
        case IDM_ELLIPSE_DIRECT: {
            vars.currentOption = IDM_ELLIPSE_DIRECT;
            break;
        }
        case IDM_ELLIPSE_POLAR: {
            vars.currentOption = IDM_ELLIPSE_POLAR;
            break;
        }
        case IDM_ELLIPSE_MIDPOINT: {
            vars.currentOption = IDM_ELLIPSE_MIDPOINT;
            break;
        }

            // Clipping
        case IDM_CLIP_RECT_POINT: {
            vars.currentOption = IDM_CLIP_RECT_POINT;
            break;
        }
        case IDM_CLIP_RECT_LINE: {
            vars.currentOption = IDM_CLIP_RECT_LINE;
            break;
        }
        case IDM_CLIP_RECT_POLY: {
            vars.currentOption = IDM_CLIP_RECT_POLY;
            break;
        }
        case IDM_CLIP_SQUARE_POINT: {
            vars.currentOption = IDM_CLIP_SQUARE_POINT;
            break;
        }
        case IDM_CLIP_SQUARE_LINE: {
            vars.currentOption = IDM_CLIP_SQUARE_LINE;
            break;
        }

    }
}

void HandleLeftButtonDOWN(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars){
    switch (vars.currentOption) {
        case IDM_CIRCLE_DIRECT:
        case IDM_CIRCLE_POLAR:
        case IDM_CIRCLE_ITER_POLAR:
        case IDM_CIRCLE_MIDPOINT:
        case IDM_CIRCLE_MOD_MID:{
            vars.xc = LOWORD(lp);
            vars.yc = HIWORD(lp);
            break;
        }
        default:
            break;
    }
}
void HandleLeftButtonUP(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars& vars) {
    switch (vars.currentOption) {
        case IDM_CIRCLE_DIRECT:
        case IDM_CIRCLE_POLAR:
        case IDM_CIRCLE_ITER_POLAR:
        case IDM_CIRCLE_MIDPOINT:
        case IDM_CIRCLE_MOD_MID: {
            hdc = GetDC(hwnd);
            int x, y, r;
            x = LOWORD(lp);
            y = HIWORD(lp);
            r = static_cast<int>(sqrt((x - vars.xc) * (x - vars.xc) + (y - vars.yc) * (y - vars.yc)));
            switch (vars.currentOption) {
                case IDM_CIRCLE_DIRECT: {
                    DrawCircleDirect(hdc, vars.xc, vars.yc, r, vars.c);
                    break;
                }
                case IDM_CIRCLE_POLAR:
                case IDM_CIRCLE_ITER_POLAR:
                case IDM_CIRCLE_MIDPOINT:
                case IDM_CIRCLE_MOD_MID: {
                    DrawCircleModifiedMidpoint(hdc, vars.xc, vars.yc, r, vars.c);
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
}
void HandleRightButtonDOWN(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars){}

