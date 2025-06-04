#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Utils.h"
#include "../Include/Filling.h"
using namespace std;

void InitTable(Table t) {
    for (int i = 0; i < 1000; ++i) {
        t[i].xLeft = INT_MAX;
        t[i].xRight = INT_MIN;
    }
}

void edge2Table(POINT p1, POINT p2, Table t) {
    if (p2.y == p1.y) return;
    if (p1.y > p2.y) swap(p1, p2);
    double x = p1.x;
    int y = p1.y;
    double mInv = (double)(p2.x - p1.x) / (p2.y - p1.y);

    while (y < p2.y) {
        if (x < t[y].xLeft) t[y].xLeft = ceil(x);
        if (x > t[y].xRight) t[y].xRight = floor(x);
        y++;
        x += mInv;
    }
}

void polygonToTable(POINT p[], int n, Table t) {
    POINT v1 = p[n - 1];
    for (int i = 0; i < n; ++i) {
        POINT v2 = p[i];
        edge2Table(v1, v2, t);
        v1 = p[i];
    }
}

void tableToScreen(HDC hdc, Table t, COLORREF c) {
    for (int i = 0; i < 1000; ++i) {
        if (t[i].xLeft < t[i].xRight) {
            for (int x = t[i].xLeft; x <= t[i].xRight; ++x) {
                SetPixel(hdc, x, i, c);
            }
        }
    }
}

void ConvexFill(HDC hdc, const vector<POINT>& p, COLORREF c) {
    Table t;
    InitTable(t);
    polygonToTable((POINT*)&p[0], p.size(), t);
    tableToScreen(hdc, t, c);
}

void FillQuarterLine(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c) {
    int dx = px - xc;
    int dy = py - yc;

    if (dx * dx + dy * dy > r * r) return;

    int quarter = -1;
    if (dx >= 0 && dy <= 0) quarter = 1;     // Q1: Top-right
    else if (dx <= 0 && dy <= 0) quarter = 2; // Q2: Top-left
    else if (dx <= 0 && dy >= 0) quarter = 3; // Q3: Bottom-left
    else if (dx >= 0 && dy >= 0) quarter = 4; // Q4: Bottom-right

    for (int y = -r; y <= r; y++) {
        int x_limit = static_cast<int>(sqrt(r * r - y * y));
        int y_pos = yc + y;

        switch (quarter) {
            case 1:
                if (y <= 0) {
                    for (int x = 0; x <= x_limit; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
            case 2:
                if (y <= 0) {
                    for (int x = -x_limit; x <= 0; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
            case 3:
                if (y >= 0) {
                    for (int x = -x_limit; x <= 0; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
            case 4:
                if (y >= 0) {
                    for (int x = 0; x <= x_limit; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
        }
    }
}

void FillQuarterWithCircles(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c) {
    int dx = px - xc;
    int dy = py - yc;

    if (dx * dx + dy * dy > r * r)
        return;

    int quarter = -1;
    if (dx >= 0 && dy <= 0) quarter = 1;
    else if (dx <= 0 && dy <= 0) quarter = 2;
    else if (dx <= 0 && dy >= 0) quarter = 3;
    else if (dx >= 0 && dy >= 0) quarter = 4;

    for (int r1 = r; r1 >= 1; r1--) {
        DrawQuarterCircle(hdc, xc, yc, r1, quarter, c);
    }
}

void FloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor) {
    stack<POINT> s;
    s.push({ x, y });

    while (!s.empty()) {
        POINT p = s.top();
        s.pop();

        COLORREF current = GetPixel(hdc, p.x, p.y);
        if (current == borderColor || current == fillColor)
            continue;

        SetPixel(hdc, p.x, p.y, fillColor);

        s.push({ p.x + 1, p.y });
        s.push({ p.x - 1, p.y });
        s.push({ p.x, p.y + 1 });
        s.push({ p.x, p.y - 1 });
    }
}

void FloodFillRec(HDC hdc , int x ,int y , COLORREF borderColor, COLORREF fillColor) {
    COLORREF c = GetPixel(hdc, x, y );
    if (c==borderColor || c==fillColor) return;
    SetPixel(hdc,x,y,fillColor);
    FloodFillRec(hdc,x+1,y,borderColor,fillColor);
    FloodFillRec(hdc,x-1,y,borderColor,fillColor);
    FloodFillRec(hdc,x,y+1,borderColor,fillColor);
    FloodFillRec(hdc,x,y-1,borderColor,fillColor);
}
