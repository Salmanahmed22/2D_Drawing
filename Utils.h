#include "windows.h"
#include <bits/stdc++.h>
using namespace std;

class Utils {
public:
    static int Round(double x);
    static void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c);
    static COLORREF InterpolateColor(float t, int r1, int g1, int b1, int r2, int g2, int b2 );
};

