#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Utils.h"

using namespace std;

void DrawCircleDirect(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    int x = 0, y = R;
    Draw8Points(hdc, xc, yc, x, y, c);

    while (x < y)
    {
        x++;
        y = Round(sqrt(R * R - x * x));
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}

void DrawCirclePolar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    int x = R, y = 0;
    Draw8Points(hdc, xc, yc, x, y, c);

    double theta = 0, dtheta = 1.0 / R;
    while (x > y)
    {
        theta += dtheta;
        x = Round(R * cos(theta));
        y = Round(R * sin(theta));
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}

void DrawCircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double x = R, y = 0;
    double dtheta = 1.0 / R;
    double ct = cos(dtheta), st = sin(dtheta);
    Draw8Points(hdc, xc, yc, R, 0, c);

    while (x > y)
    {
        double x1 = x * ct - y * st;
        y = x * st + y * ct;
        x = x1;
        Draw8Points(hdc, xc, yc, Round(x), Round(y), c);
    }
}

void DrawCircleBresenham(HDC hdc, int xc, int yc, int r, COLORREF c) {
    int x = 0, y = r;
    int d = 1 - r;
    Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}

void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c) {
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