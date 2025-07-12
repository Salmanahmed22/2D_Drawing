#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Var&defines.h"
using namespace std;

#ifndef INC_2D_DRAWING_CURVES_H
#define INC_2D_DRAWING_CURVES_H

struct Point2D{
    double x, y;
    Point2D(double x = 0.0, double y = 0.0):x(x),y(y){};
};
void DrawHermiteCurve(HDC hdc , int x1, int y1 , int u1, int v1 , int x2, int y2 , int u2, int v2, COLORREF c);
void DrawBezierCurve(HDC hdc, const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3, COLORREF c);
void DrawCardinalSpline(HDC hdc, Point2D P[], int n, double c, COLORREF color);

#endif //INC_2D_DRAWING_CURVES_H
