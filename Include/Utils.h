#include "windows.h"
#include <bits/stdc++.h>
using namespace std;


int Round(double x);
void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c);
COLORREF InterpolateColor(float t, int r1, int g1, int b1, int r2, int g2, int b2 );
void computeBezierCoefficients(const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3,
                                          POINT& alpha, POINT& beta, POINT& gamma, POINT& delta);
POINT bezierPoint(double t, const POINT& alpha, const POINT& beta, const POINT& gamma, const POINT& delta);
void makeSquareWindow(int xleft,int xright, int ybottom, int ytop);
void makeRectangularWindow(int xleft,int xright, int ybottom, int ytop);
void Draw2Points(HDC hdc, int xc, int yc, int x, int y, int quarter, COLORREF c);
void DrawQuarterCircle(HDC hdc, int xc, int yc, int r, int quarter, COLORREF c);


