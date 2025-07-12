#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Circle.h"
#include "../Include/Var&defines.h"
#include "../Include/Clipping.h"
#include "../Include/Filling.h"
#include "../Include/Line.h"
#include "../Include/Ellipse.h"
using namespace std;

void SaveWindow(HWND hwnd) {
    char filename[MAX_PATH] = "";
    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Bitmap Files (*.bmp)\0*.bmp\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "bmp";

    if (!GetSaveFileName(&ofn)) {
        return;
    }

    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right;
    int height = rect.bottom;

    HDC hdcWindow = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdcWindow);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, width, height);
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    int rowSize = ((width * 3 + 3) & ~3);
    int dataSize = rowSize * height;
    BYTE* pixels = new BYTE[dataSize];
    GetDIBits(hdcMem, hBitmap, 0, height, pixels, &bmi, DIB_RGB_COLORS);

    ofstream file(filename, ios::binary);
    file.write((char*)&width, sizeof(int));
    file.write((char*)&height, sizeof(int));
    file.write((char*)pixels, dataSize);
    file.close();

    string photoName = string(filename) + ".bmp";
    BITMAPFILEHEADER bfh = {};
    bfh.bfType = 0x4D42;
    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    ofstream bmpFile(photoName, ios::binary);
    bmpFile.write((char*)&bfh, sizeof(bfh));
    bmpFile.write((char*)&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
    bmpFile.write((char*)pixels, dataSize);
    bmpFile.close();

    delete[] pixels;
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdcWindow);

    MessageBox(hwnd, "Window saved successfully.", "Saved", MB_OK);
}

void LoadWindow(HWND hwnd) {
    char filename[MAX_PATH] = "";
    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Bitmap Files (*.bmp)\0*.bmp\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt = "bmp";

    if (!GetOpenFileName(&ofn)) {
        return;
    }

    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        MessageBox(hwnd, "Failed to open file.", "Error", MB_OK);
        return;
    }

    int width, height;
    file.read((char*)&width, sizeof(int));
    file.read((char*)&height, sizeof(int));

    int rowSize = ((width * 3 + 3) & ~3);
    int dataSize = rowSize * height;
    BYTE* pixels = new BYTE[dataSize];
    file.read((char*)pixels, dataSize);
    file.close();

    HDC hdcWindow = GetDC(hwnd);
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(
            hdcWindow,
            0, 0, width, height,
            0, 0, width, height,
            pixels,
            &bmi,
            DIB_RGB_COLORS,
            SRCCOPY
    );

    delete[] pixels;
    ReleaseDC(hwnd, hdcWindow);

    MessageBox(hwnd, "Window loaded successfully.", "Loaded", MB_OK);
}

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
    AppendMenu(hOptions, MF_STRING, IDM_CLEAR, "Clear");

    // Final Menu Bar
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hOptions, "Options");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hShapes, "Shapes");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFilling, "Filling");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hClipping, "Clipping");

    return hMenuBar;
}

void HandleChoice(HBRUSH &hBackgroundBrush,HCURSOR &hCurrentCursor,HWND hwnd,WPARAM wp,LPARAM lp,HDC hdc,Vars &vars){
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
            SaveWindow(hwnd);
            break;
        }
        case IDM_LOAD: {
            LoadWindow(hwnd);
            break;
        }
        case IDM_CLEAR: {
            InvalidateRect(hwnd, nullptr, TRUE);
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
            hdc = GetDC(hwnd);
            drawWindow(vars.rectangleWindow,hdc, RGB(0,0,0));
            vars.currentOption = IDM_CLIP_RECT_POINT;
            break;
        }
        case IDM_CLIP_RECT_LINE: {
            hdc = GetDC(hwnd);
            drawWindow(vars.rectangleWindow,hdc, RGB(0,0,0));
            vars.currentOption = IDM_CLIP_RECT_LINE;
            break;
        }
        case IDM_CLIP_RECT_POLY: {
            int n;
            cout<< "enter number of polygon vertices: ";
            cin>> n;
            hdc = GetDC(hwnd);
            drawWindow(vars.rectangleWindow,hdc, RGB(0,0,0));
            vars.currentOption = IDM_CLIP_RECT_POLY;
            vars.polygonPointsExpected = n;
            break;
        }
        case IDM_CLIP_SQUARE_POINT: {
            hdc = GetDC(hwnd);
            drawWindow(vars.squareWindow,hdc, RGB(0,0,0));
            vars.currentOption = IDM_CLIP_SQUARE_POINT;
            break;
        }
        case IDM_CLIP_SQUARE_LINE: {
            hdc = GetDC(hwnd);
            drawWindow(vars.squareWindow,hdc, RGB(0,0,0));
            vars.currentOption = IDM_CLIP_SQUARE_LINE;
            break;
        }

    }
}

void HandleLeftButtonDOWN(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars){
    switch (vars.currentOption) {
        //circle
        case IDM_CIRCLE_DIRECT:
        case IDM_CIRCLE_POLAR:
        case IDM_CIRCLE_ITER_POLAR:
        case IDM_CIRCLE_MIDPOINT:
        case IDM_CIRCLE_MOD_MID:{
            vars.xc = LOWORD(lp);
            vars.yc = HIWORD(lp);
            break;
        }
        //clipping
        case IDM_CLIP_RECT_LINE:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            break;
        }
        case IDM_CLIP_RECT_POLY:{
            int x = LOWORD(lp);
            int y = HIWORD(lp);
            hdc = GetDC(hwnd);
            // Draw a small dot for visual feedback
            Ellipse(hdc, x - 3, y - 3, x + 3, y + 3);
            ReleaseDC(hwnd, hdc);
            POINT p = {x, y};
            vars.polygonPoints.push_back(p);

            hdc = GetDC(hwnd);
            SetPixel(hdc, x, y, RGB(0, 0, 255)); // Visualize click
            ReleaseDC(hwnd, hdc);

            if (vars.polygonPoints.size() == vars.polygonPointsExpected) {
                hdc = GetDC(hwnd);
                polygonClipping(hdc, vars.polygonPoints, vars.rectangleWindow, vars.c);
                vars.polygonPoints.clear();
            }
        }
        case IDM_CLIP_RECT_POINT:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            POINT p1;
            p1.x = vars.x1;
            p1.y = vars.y1;
            if (pointClipping(p1,vars.rectangleWindow)){
                hdc = GetDC(hwnd);
                Ellipse(hdc, p1.x - 3, p1.y - 3, p1.x + 3, p1.y + 3);
                ReleaseDC(hwnd, hdc);
            }
            break;
        }
        case IDM_CLIP_SQUARE_LINE:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            break;
        }
        case IDM_CLIP_SQUARE_POINT:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            POINT p1;
            p1.x = vars.x1;
            p1.y = vars.y1;
            if (pointClipping(p1,vars.squareWindow)){
                hdc = GetDC(hwnd);
                Ellipse(hdc, p1.x - 3, p1.y - 3, p1.x + 3, p1.y + 3);
                ReleaseDC(hwnd, hdc);
            }
            break;
        }
        case IDM_CARDINAL_SPLINE: {
            Point2D p;
            p.x = LOWORD(lp);
            p.y = HIWORD(lp);

            vars.cardinalSplinePoints.push_back(p);

            hdc = GetDC(hwnd);
            Ellipse(hdc, p.x - 2, p.y - 2, p.x + 2, p.y + 2);  // Visual feedback
            ReleaseDC(hwnd, hdc);
            break;
        }


            //filling
        case IDM_FLOOD_NONREC: {
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            hdc = GetDC(hwnd);
            FloodFill(hdc,vars.x1,vars.y1, vars.c,vars.c);
            break;
        }
        case IDM_FILL_CIRCLE_LINES: {
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            hdc = GetDC(hwnd);
            FillQuarterLine(hdc,vars.xc,vars.yc,vars.r,vars.x1,vars.y1,vars.c);
            break;
        }
        case IDM_FILL_CIRCLE_CIRC: {
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            hdc = GetDC(hwnd);
            FillQuarterWithCircles(hdc,vars.xc,vars.yc,vars.r,vars.x1,vars.y1,vars.c);
            break;
        }
        case IDM_FILL_CONVEX:
        case IDM_FILL_NONCONVEX:{
            int x = LOWORD(lp);
            int y = HIWORD(lp);
            POINT pt = {x, y};
            if(vars.currentOption == IDM_FILL_CONVEX)
                vars.convexPoints.push_back(pt);
            else if(vars.currentOption == IDM_FILL_NONCONVEX)
                vars.nonConvexPoints.push_back(pt);
            hdc = GetDC(hwnd);
            Ellipse(hdc, x - 3, y - 3, x + 3, y + 3);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case IDM_FLOOD_RECURSIVE: {
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            hdc = GetDC(hwnd);
            FloodFillRec(hdc,vars.x1,vars.y1, vars.c,vars.c);
            break;
        }
        case IDM_FILL_SQUARE_HERM: {
            int x = LOWORD(lp);
            int y = HIWORD(lp);

            switch (vars.clickCount) {
                case 0:
                    vars.squareTopLeft = { x, y };
                    break;

                case 1:
                    vars.squareBottomRight = { x, y };
                    vars.squareSize = abs(vars.squareBottomRight.x - vars.squareTopLeft.x);
                    break;

                case 2:
                    vars.tangentClickTop = { x, y };
                    vars.R0 = { vars.tangentClickTop.x - vars.squareTopLeft.x, vars.tangentClickTop.y - vars.squareTopLeft.y };
                    break;

                case 3: {
                    vars.tangentClickBottom = {x, y};
                    POINT bottomPoint = {vars.squareTopLeft.x, vars.squareTopLeft.y + vars.squareSize};
                    vars.R1 = {vars.tangentClickBottom.x - bottomPoint.x, vars.tangentClickBottom.y - bottomPoint.y};

                    // Now draw directly after all 4 points are ready
                    HDC hdc = GetDC(hwnd);
                    FillSquareWithVerticalHermite(hdc, vars.squareTopLeft, vars.squareSize, vars.R0, vars.R1,
                                                 vars.c);
                    ReleaseDC(hwnd, hdc);
                    break;
                }
                default:
                    break;
            }

            vars.clickCount = (vars.clickCount + 1) % 4;
            break;
        }

        case IDM_FILL_RECT_BEZIER: {
            POINT p = { LOWORD(lp), HIWORD(lp) };
            vars.BezzierPoints.push_back(p);

            // Optional: draw a small visual dot
            HDC hdc = GetDC(hwnd);
            Ellipse(hdc, p.x - 3, p.y - 3, p.x + 3, p.y + 3);
            ReleaseDC(hwnd, hdc);

            if (vars.BezzierPoints.size() == 3) {
                RECT rect;
                ComputeRectangleFromPoints(vars.BezzierPoints, rect);

                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;

                hdc = GetDC(hwnd);
                FillRectangleWithBezierHorizontal(hdc, rect.left, rect.top, width, height, vars.c);
                ReleaseDC(hwnd, hdc);

                vars.BezzierPoints.clear(); // ✅ Reset for next shape
            }

            break;
        }

            //line
        case  IDM_LINE_PARAMETRIC:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            break;
        }
        case  IDM_LINE_MIDPOINT:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            break;
        }
        case  IDM_LINE_DDA:{
            vars.x1 = LOWORD(lp);
            vars.y1 = HIWORD(lp);
            break;
        }
        //ellipse
        case IDM_ELLIPSE_DIRECT:{
            // Save center of ellipse
            vars.xc = LOWORD(lp);
            vars.yc = HIWORD(lp);
            break;
        }
        case IDM_ELLIPSE_POLAR:{
            vars.xc = LOWORD(lp);
            vars.yc = HIWORD(lp);
            break;
        }
        case IDM_ELLIPSE_MIDPOINT:{
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
            int x, y;
            x = LOWORD(lp);
            y = HIWORD(lp);
            vars.r = static_cast<int>(sqrt((x - vars.xc) * (x - vars.xc) + (y - vars.yc) * (y - vars.yc)));
            switch (vars.currentOption) {
                case IDM_CIRCLE_DIRECT: {
                    DrawCircleDirect(hdc, vars.xc, vars.yc, vars.r, vars.c);
                    break;
                }
                case IDM_CIRCLE_POLAR:{
                    DrawCirclePolar(hdc, vars.xc, vars.yc, vars.r, vars.c);
                    break;
                }
                case IDM_CIRCLE_ITER_POLAR:{
                    DrawCircleIterativePolar(hdc, vars.xc, vars.yc, vars.r, vars.c);
                    break;
                }
                case IDM_CIRCLE_MIDPOINT:{
                    DrawCircleBresenham(hdc, vars.xc, vars.yc, vars.r, vars.c);
                    break;
                }
                case IDM_CIRCLE_MOD_MID: {
                    DrawCircleModifiedMidpoint(hdc, vars.xc, vars.yc, vars.r, vars.c);
                    break;
                }
                default:
                    break;
            }
            ReleaseDC(hwnd, hdc);
            break;
        }

        case IDM_CLIP_RECT_LINE:{
            hdc = GetDC(hwnd);
            vars.x2 = LOWORD(lp);
            vars.y2 = HIWORD(lp);
            POINT p1,p2;
            p1.x = vars.x1;
            p1.y = vars.y1;
            p2.x = vars.x2;
            p2.y = vars.y2;
            CohenSutherland(p1,p2,vars.rectangleWindow,hdc,vars.c);
            break;
        }
        case IDM_CLIP_SQUARE_LINE:{
            hdc = GetDC(hwnd);
            vars.x2 = LOWORD(lp);
            vars.y2 = HIWORD(lp);
            POINT p1,p2;
            p1.x = vars.x1;
            p1.y = vars.y1;
            p2.x = vars.x2;
            p2.y = vars.y2;
            CohenSutherland(p1,p2,vars.squareWindow,hdc,vars.c);
            break;
        }

        case IDM_LINE_MIDPOINT:{
            hdc = GetDC(hwnd);
            vars.x2 = LOWORD(lp);
            vars.y2 = HIWORD(lp);
            DrawLineMidPoint(hdc,vars.x1,vars.y1,vars.x2,vars.y2,vars.c);
            break;
        }
        case IDM_LINE_PARAMETRIC:{
            hdc = GetDC(hwnd);
            vars.x2 = LOWORD(lp);
            vars.y2 = HIWORD(lp);
            DrawLineParametric(hdc, vars.x1, vars.y1, vars.x2, vars.y2, vars.c);
            break;

        }
        case IDM_LINE_DDA:{
            hdc = GetDC(hwnd);
            vars.x2 = LOWORD(lp);
            vars.y2 = HIWORD(lp);
            DrawLineDDA(hdc, vars.x1, vars.y1, vars.x2, vars.y2, vars.c);
            break;
        }

        case IDM_ELLIPSE_DIRECT:{
            hdc = GetDC(hwnd);
            int x, y;
            x = LOWORD(lp);
            y = HIWORD(lp);
            int a = abs(x - vars.xc); // Horizontal radius
            int b = abs(y - vars.yc); // Vertical radius
            DrawEllipseDirect(hdc, vars.xc, vars.yc, a, b, vars.c);
            break;
        }
        case IDM_ELLIPSE_POLAR:{
            hdc = GetDC(hwnd);
            int x, y;
            x = LOWORD(lp);
            y = HIWORD(lp);
            int a = abs(x - vars.xc);
            int b = abs(y - vars.yc);
            DrawEllipsePolar(hdc, vars.xc, vars.yc, a, b, vars.c);
            break;
        }
        case IDM_ELLIPSE_MIDPOINT:{
            hdc = GetDC(hwnd);
            int x, y;
            x = LOWORD(lp);
            y = HIWORD(lp);
            int a = abs(x - vars.xc);
            int b = abs(y - vars.yc);
            DrawEllipseMidpoint(hdc, vars.xc, vars.yc, a, b, vars.c);
            break;
        }
        default:
            break;
    }
}

void HandleRightButtonDOWN(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars){
    switch (vars.currentOption){
        case IDM_FILL_CONVEX:{
            if (vars.convexPoints.size() < 3) break;
            hdc = GetDC(hwnd);
            ConvexFill(hdc, vars.convexPoints, vars.c);
            ReleaseDC(hwnd, hdc);
            vars.convexPoints.clear();
            break;
        }
        case IDM_FILL_NONCONVEX:{
            if(vars.nonConvexPoints.size() >= 3){
                hdc = GetDC(hwnd);
                GeneralFill(hdc, vars.nonConvexPoints, vars.c);
                ReleaseDC(hwnd, hdc);
                vars.nonConvexPoints.clear();
            }
            break;
        }
        case IDM_CARDINAL_SPLINE: {
            if (vars.cardinalSplinePoints.size() >= 4) {
                hdc = GetDC(hwnd);
                DrawCardinalSpline(hdc, vars.cardinalSplinePoints.data(), (int)vars.cardinalSplinePoints.size(), 0.5, vars.c);
                ReleaseDC(hwnd, hdc);
            }
            vars.cardinalSplinePoints.clear();
            break;
        }

        default:
            break;
    }
}



