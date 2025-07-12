#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Utils.h"
#include "../Include/Curves.h"


using namespace std;

void DrawHermiteCurve(HDC hdc , int x1, int y1 , int u1, int v1 , int x2, int y2 , int u2, int v2, COLORREF c){
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
        SetPixel(hdc, Round(x), Round(y),c);
    }
}
void DrawBezierCurve(HDC hdc, const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3, COLORREF c) {
    POINT alpha, beta, gamma, delta;
    computeBezierCoefficients(P0, P1, P2, P3, alpha, beta, gamma, delta);

    const int steps = 1000;
    for (int i = 0; i <= steps; ++i) {
        double t = (double)i / steps;
        POINT pt = bezierPoint(t, alpha, beta, gamma, delta);
        SetPixel(hdc, Round(pt.x), Round(pt.y), c);
    }
}
void DrawCardinalSpline(HDC hdc, Point2D P[], int n, double c, COLORREF color) {
    if (n < 4) return;
    double s = c/2.0;
    for (int i = 1; i < n - 2; ++i) {
        int T1x = (int)(s * (P[i + 1].x - P[i - 1].x));
        int T1y = (int)(s * (P[i + 1].y - P[i - 1].y));
        int T2x = (int)(s * (P[i + 2].x - P[i].x));
        int T2y = (int)(s * (P[i + 2].y - P[i].y));

        DrawHermiteCurve(
                hdc,
                (int)P[i].x, (int)P[i].y,T1x, T1y,
                (int)P[i + 1].x, (int)P[i + 1].y,T2x, T2y,
                color
        );
    }
}
