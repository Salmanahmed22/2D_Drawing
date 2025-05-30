#include <windows.h>

class Algorithms {
public:
    static void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color);
    static void DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c);
    static void InterpolatedColoredLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
    static void drawHermiteCurve(HDC hdc , int x1, int y1 , int u1, int v1 , int x2, int y2 , int u2, int v2, COLORREF c);
    static void drawBezierCurve(HDC hdc, const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3);
    static void FloodFill(HDC hdc, int x, int y, COLORREF targetColor, COLORREF fillColor);
};

