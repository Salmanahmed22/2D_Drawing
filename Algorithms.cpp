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

//Curves

//hermite
void Algorithms::drawHermiteCurve(HDC hdc , int x1, int y1 , int u1, int v1 , int x2, int y2 , int u2, int v2, COLORREF c){
    int hermiteMatrix[4][4] = {
            { 2, -2,  1,  1 },
            {-3,  3, -2, -1 },
            { 0,  0,  1,  0 },
            { 1,  0,  0,  0 }
    };
    int xc[4] = {x1,x2,u1,u2};
    int yc[4] = {y1,y2,v1,v2};

    double a[4], b[4];

    for (int i = 0; i < 4; i++) {
        a[i] = b[i] = 0;
        for (int j = 0; j < 4; j++) {
            a[i] += hermiteMatrix[i][j] * xc[j];
            b[i] += hermiteMatrix[i][j] * yc[j];
        }
    }

    for (double t = 0; t <= 1; t+=0.001) {
        double x = a[0]*pow(t,3) + a[1]*pow(t,2) + a[2]*t + a[3];
        double y = b[0]*pow(t,3) + b[1]*pow(t,2) + b[2]*t + b[3];
        SetPixel(hdc, Utils::Round(x), Utils::Round(y),c);
    }
}

//bezier

void Algorithms::drawBezierCurve(HDC hdc, const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3) {
    POINT alpha, beta, gamma, delta;
    Utils::computeBezierCoefficients(P0, P1, P2, P3, alpha, beta, gamma, delta);

    const int steps = 1000;
    for (int i = 0; i <= steps; ++i) {
        double t = (double)i / steps;
        POINT pt = Utils::bezierPoint(t, alpha, beta, gamma, delta);
        SetPixel(hdc, Utils::Round(pt.x), Utils::Round(pt.y), RGB(255, 0, 0)); // Red pixel
    }
}


//flood fill
void Algorithms::FloodFill(HDC hdc, int x, int y, COLORREF targetColor, COLORREF fillColor) {
    stack<POINT> s;
    s.push({ x, y });

    while (!s.empty()) {
        POINT p = s.top();
        s.pop();

        COLORREF current = GetPixel(hdc, p.x, p.y);
        if (current != targetColor || current == fillColor)
            continue;

        SetPixel(hdc, p.x, p.y, fillColor);

        s.push({ p.x + 1, p.y });
        s.push({ p.x - 1, p.y });
        s.push({ p.x, p.y + 1 });
        s.push({ p.x, p.y - 1 });
    }
}


