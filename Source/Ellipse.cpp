#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Var&defines.h"
#include "../Include/Utils.h"
using namespace std;


void DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
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

void draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc + x, yc - y, c);
}

void DrawEllipsePolar(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    double step = 1.0 / max(a , b) , limit = 0.5 * M_PI;
    for (double theta = 0; theta <= limit ; theta += step) {
        int x = (int)round(a * cos(theta));
        int y = (int)round(b * sin(theta));
        draw4Points(hdc, xc, yc, x, y, c);
    }
}


void DrawEllipseMidpoint(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    int x = a;
    int y = 0;
    double a2 = a * a, b2 = b * b;
    double d = a2 - b2 * a + 0.25 * b2; //initially: x => (a - 0.5) , y => (0 + 1)
    int dx = 2 * b2 * x;
    int dy = 2 * a2 * y;
    draw4Points(hdc, xc, yc, x, y, c);

    while (dy < dx) {
        if (d < 0) {
            y++;
            dy += 2 * a2;
            d += dy + a2;
        } else {
            y++;
            x--;
            dx -= 2 * b2;
            dy += 2 * a2;
            d += a2 + dy - dx;
        }
        draw4Points(hdc, xc, yc, x, y, c);
    }

    d = a2 * (y + 0.5) * (y + 0.5) + b2 * (x - 1) * (x - 1) - a2 * b2;  //x => (x - 0.5) , y => (y + 1)
    while (x >= 0) {
        if (d > 0) {
            x--;
            dx -= 2 * b2;
            d += b2 - dx;
        } else {
            x--;
            y++;
            dx -= 2 * b2;
            dy += 2 * a2;
            d += dy - dx + b2;
        }
        draw4Points(hdc, xc, yc, x, y, c);
    }
}
