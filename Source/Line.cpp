#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Utils.h"

using namespace std;

void DrawParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int alpha1 = x2 - x1, alpha2 = y2 - y1;

    float step = 1.0 / max(abs(alpha1),abs(alpha2));

    for (float t = 0.0; t <= 1.0; t+=step) {
        float x = float (alpha1)*t + x1;
        float y = float(alpha2)*t + y1;
        SetPixel(hdc, Round(x), Round(y),c);
    }
}

void DrawLineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    SetPixel(hdc, x, y, c);
    if (dx > dy) // slope <= 1
    {
        int d = -2 * dy + dx;
        int d1 = -2 * dy;
        int d2 = 2 * (dx - dy);
        while (x != x2)
        {
            if (d < 0)
            {
                d += d2;
                x += sx;
                y += sy;
            }
            else
            {
                d += d1;
                x += sx;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else // slope > 1
    {
        int d = -2 * dx + dy;
        int d1 = -2 * dx;
        int d2 = 2 * (dy - dx);
        while (y != y2)
        {
            if (d < 0)
            {
                d += d2;
                y += sy;
                x += sx;
            }
            else
            {
                d += d1;
                y += sy;
            }
            SetPixel(hdc, x, y, c);
        }
    }
}