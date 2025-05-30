#include "windows.h"
#include <bits/stdc++.h>
using namespace std;

class Utils {
public:
    static int Round(double x);
    static void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c);
    static COLORREF InterpolateColor(float t, int r1, int g1, int b1, int r2, int g2, int b2 );
    static void computeBezierCoefficients(const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3,
                                          POINT& alpha, POINT& beta, POINT& gamma, POINT& delta);
    static POINT bezierPoint(double t, const POINT& alpha, const POINT& beta, const POINT& gamma, const POINT& delta);
    static void makeSquareWindow(int xleft,int xright, int ybottom, int ytop);
    static void makeRectangularWindow(int xleft,int xright, int ybottom, int ytop);
};

