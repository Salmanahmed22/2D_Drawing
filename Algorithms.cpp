#include "Algorithms.h"
#include "Utils.h"
#include <bits/stdc++.h>
using namespace std;


//Circle
void Algorithms::DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    int d = 1 - R;
    int d1 = 3, d2 = 5 - 2 * R;
    Utils::Draw8Points(hdc, xc, yc, x, y, c);
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
        Utils::Draw8Points(hdc, xc, yc, x, y, c);
    }
}


//Ellipse
void Algorithms::DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    // calc y from x from -a to a
    for (int x = -a; x <= a; x++) {
        double y = b * sqrt(1.0 - (double)(x * x) / (a * a));
        int ry = Utils::Round(y);
        SetPixel(hdc, xc + x, yc + ry, c);
        SetPixel(hdc, xc + x, yc - ry, c);
    }

    // calc x from y from -b to b
    for (int y = -b; y <= b; y++) {
        double x = a * sqrt(1.0 - (double)(y * y) / (b * b));
        int rx = Utils::Round(x);
        SetPixel(hdc, xc + rx, yc + y, c);
        SetPixel(hdc, xc - rx, yc + y, c);
    }
}

//Line
void Algorithms::InterpolatedColoredLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int alpha1 = x2 - x1, alpha2 = y2 - y1;

    float step = 1.0 / max(abs(alpha1),abs(alpha2));

    for (float t = 0.0; t <= 1.0; t+=step) {
        float x = float (alpha1)*t + x1;
        float y = float(alpha2)*t + y1;
        SetPixel(hdc, Utils::Round(x), Utils::Round(y),c);
    }
}