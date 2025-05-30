#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
struct Window {
    int leftX, rightX, bottomY, topY;
    Window(int leftX = 0, int rightX = 0, int bottomY = 0, int topY = 0)
            : leftX(leftX), rightX(rightX), bottomY(bottomY), topY(topY) {}
};
void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color);
void DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c);
void drawParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
void DrawHermiteCurve(HDC hdc , int x1, int y1 , int u1, int v1 , int x2, int y2 , int u2, int v2, COLORREF c);
void DrawBezierCurve(HDC hdc, const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3);
void FloodFill(HDC hdc, int x, int y, COLORREF targetColor, COLORREF fillColor);
void CohenSutherland(POINT p1, POINT p2, Window window);
void polygonClipping(HDC hdc, vector<POINT> ps, Window window, COLORREF c);

