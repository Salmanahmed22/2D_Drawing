#pragma once
#include <windows.h>

namespace DrawingManager {
    void drawLineDDA(HDC hdc, POINT p1, POINT p2, COLORREF color);
    void drawLineMidpoint(HDC hdc, POINT p1, POINT p2, COLORREF color);
    void drawCircleMidpoint(HDC hdc, POINT center, int radius, COLORREF color);
    void drawEllipseMidpoint(HDC hdc, POINT center, int rx, int ry, COLORREF color);
    // ... other algorithms
}
