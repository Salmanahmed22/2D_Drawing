#include <windows.h>

class Algorithms {
public:
    static void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color);
    static void DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c);
    static void InterpolatedColoredLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);
};

