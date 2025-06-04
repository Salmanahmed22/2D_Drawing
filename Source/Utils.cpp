#include "windows.h"
#include <bits/stdc++.h>
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

//========================\\