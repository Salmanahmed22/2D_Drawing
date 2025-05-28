#include "Algorithms.h"
#include <bits/stdc++.h>
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

//========================\\

//Circle
void Algorithms::DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    int d = 1 - R;
    int d1 = 3, d2 = 5 - 2 * R;
    Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += d1;
            d2 += 2;
            x++;
        } else {
            d += d2;
            d2 += 4;
            x++;
            y--;
        }
        d1 += 2;
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}


//Ellipse
void Algorithms::DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    // calc y from x from -a to a
    for (int x = -a; x <= a; x++) {
        double y = b * sqrt(1.0 - (double)(x * x) / (a * a));
        int ry = Round(y);
        SetPixel(hdc, xc + x, yc + ry, c);
        SetPixel(hdc, xc + x, yc - ry, c);
    }

    // calc x from y from -b to b
    for (int y = -b; y <= b; y++) {
        double x = a * sqrt(1.0 - (double)(y * y) / (b * b));
        int rx = Round(x);
        SetPixel(hdc, xc + rx, yc + y, c);
        SetPixel(hdc, xc - rx, yc + y, c);
    }
}