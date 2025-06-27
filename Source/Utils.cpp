#include "windows.h"
#include <bits/stdc++.h>
#include <tchar.h>
#include "../Include/Utils.h"
#include "../Include/Clipping.h"
using namespace std;
//=========Utils========\\

int Round(double x) {
    return static_cast<int>(x + 0.5);
}

void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    // swap x and y
    swap(x, y);

    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc + x, yc - y, c);
}

COLORREF InterpolateColor(float t, int r1, int g1, int b1, int r2, int g2, int b2 ){
    int r = r1 + t * (r2 - r1);
    int g = g1 + t * (g2 - g1);
    int b = b1 + t * (b2 - b1);
    return RGB(r, g, b);
}


void computeBezierCoefficients(const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3,
                                      POINT& alpha, POINT& beta, POINT& gamma, POINT& delta) {
    delta = P0;
    gamma.x = 3 * (P1.x - P0.x);
    gamma.y = 3 * (P1.y - P0.y);
    beta.x = 3 * (P2.x - 2 * P1.x + P0.x);
    beta.y = 3 * (P2.y - 2 * P1.y + P0.y);
    alpha.x = P3.x - P0.x - gamma.x - beta.x;
    alpha.y = P3.y - P0.y - gamma.y - beta.y;
}

POINT bezierPoint(double t, const POINT& alpha, const POINT& beta, const POINT& gamma, const POINT& delta) {
    POINT p;
    p.x = alpha.x * t * t * t + beta.x * t * t + gamma.x * t + delta.x;
    p.y = alpha.y * t * t * t + beta.y * t * t + gamma.y * t + delta.y;
    return p;
}

void makeSquareWindow(int xleft, int xright, int ybottom, int ytop) {
    Window window(xleft,xright,ybottom,ytop);
}

void makeRectangularWindow(int xleft, int xright, int ybottom, int ytop) {
    Window window(xleft,xright,ybottom,ytop);
}

void Draw2Points(HDC hdc, int xc, int yc, int x, int y, int quarter, COLORREF c) {
    switch (quarter) {
        case 1: // Top-right
            SetPixel(hdc, xc + x, yc - y, c);
            SetPixel(hdc, xc + y, yc - x, c);
            break;
        case 2: // Top-left
            SetPixel(hdc, xc - x, yc - y, c);
            SetPixel(hdc, xc - y, yc - x, c);
            break;
        case 3: // Bottom-left
            SetPixel(hdc, xc - x, yc + y, c);
            SetPixel(hdc, xc - y, yc + x, c);
            break;
        case 4: // Bottom-right
            SetPixel(hdc, xc + x, yc + y, c);
            SetPixel(hdc, xc + y, yc + x, c);
            break;
    }
}

void DrawQuarterCircle(HDC hdc, int xc, int yc, int r, int quarter, COLORREF c) {
    int x = 0, y = r;
    int d = 1 - r;
    Draw2Points(hdc, xc, yc, x, y, quarter, c);

    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        Draw2Points(hdc, xc, yc, x, y, quarter, c);
    }
}

void saveBoard(HWND hwnd, HDC hdc){
//    RECT rc;
//    GetClientRect(hwnd, &rc);
//    int width = rc.right - rc.left;
//    int height = rc.bottom - rc.top;
//
//    // Create a compatible DC and bitmap
//    HDC hdcMem = CreateCompatibleDC(hdc);
//    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
//    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
//
//    // Copy the client area to the bitmap
//    BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
//
//    // Prepare the save file dialog
//    OPENFILENAME ofn;
//    TCHAR szFile[MAX_PATH] = {0};
//
//    ZeroMemory(&ofn, sizeof(ofn));
//    ofn.lStructSize = sizeof(ofn);
//    ofn.hwndOwner = hwnd;
//    ofn.lpstrFile = szFile;
//    ofn.nMaxFile = sizeof(szFile);
//    ofn.lpstrFilter = _T("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
//    ofn.nFilterIndex = 1;
//    ofn.lpstrDefExt = _T("bmp");
//    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
//
//    if (GetSaveFileName(&ofn)) {
//        // Save the bitmap to file
//        BITMAPFILEHEADER bmfHeader;
//        BITMAPINFOHEADER bi;
//
//        bi.biSize = sizeof(BITMAPINFOHEADER);
//        bi.biWidth = width;
//        bi.biHeight = height;
//        bi.biPlanes = 1;
//        bi.biBitCount = 24;
//        bi.biCompression = BI_RGB;
//        bi.biSizeImage = 0;
//        bi.biXPelsPerMeter = 0;
//        bi.biYPelsPerMeter = 0;
//        bi.biClrUsed = 0;
//        bi.biClrImportant = 0;
//
//        DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;
//        HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
//        char* lpbitmap = (char*)GlobalLock(hDIB);
//
//        GetDIBits(hdcMem, hBitmap, 0, height, lpbitmap, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
//
//        HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//
//        DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//        bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
//        bmfHeader.bfSize = dwSizeofDIB;
//        bmfHeader.bfType = 0x4D42; // "BM"
//
//        DWORD dwBytesWritten = 0;
//        WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
//        WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
//        WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);
//
//        GlobalUnlock(hDIB);
//        GlobalFree(hDIB);
//        CloseHandle(hFile);
//    }
//
//    // Clean up
//    SelectObject(hdcMem, hOldBitmap);
//    DeleteDC(hdcMem);
//    DeleteObject(hBitmap);

}

void loadBoard(HWND hwnd, HDC hdc){
//    OPENFILENAME ofn;
//    TCHAR szFile[MAX_PATH] = {0};
//
//    ZeroMemory(&ofn, sizeof(ofn));
//    ofn.lStructSize = sizeof(ofn);
//    ofn.hwndOwner = hwnd;
//    ofn.lpstrFile = szFile;
//    ofn.nMaxFile = sizeof(szFile);
//    ofn.lpstrFilter = _T("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
//    ofn.nFilterIndex = 1;
//    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
//
//    if (GetOpenFileName(&ofn)) {
//        HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, ofn.lpstrFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//        if (hBitmap) {
//            // Get the bitmap dimensions
//            BITMAP bm;
//            GetObject(hBitmap, sizeof(BITMAP), &bm);
//
//            // Create a memory DC
//            HDC hdcMem = CreateCompatibleDC(hdc);
//            HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
//
//            // Draw the loaded bitmap to the window
//            RECT rc;
//            GetClientRect(hwnd, &rc);
//            BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
//
//            // Clean up
//            SelectObject(hdcMem, hOldBitmap);
//            DeleteDC(hdcMem);
//            DeleteObject(hBitmap);
//
//            InvalidateRect(hwnd, NULL, TRUE);
//        } else {
//            MessageBox(hwnd, _T("Failed to load image"), _T("Error"), MB_OK | MB_ICONERROR);
//        }
//    }
}

//========================\\