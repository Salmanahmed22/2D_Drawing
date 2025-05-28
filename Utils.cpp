#include "Utils.h"
#include "windows.h"
#include <bits/stdc++.h>
using namespace std;
//=========Utils========\\

int Utils::Round(double x) {
    return static_cast<int>(x + 0.5);
}

void Utils::Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
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

COLORREF Utils::InterpolateColor(float t, int r1, int g1, int b1, int r2, int g2, int b2 ){
    int r = r1 + t * (r2 - r1);
    int g = g1 + t * (g2 - g1);
    int b = b1 + t * (b2 - b1);
    return RGB(r, g, b);
}
//========================\\