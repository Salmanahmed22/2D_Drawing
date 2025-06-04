#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Var&defines.h"
using namespace std;

#ifndef INC_2D_DRAWING_CIRCLE_H
#define INC_2D_DRAWING_CIRCLE_H

void DrawCircleDirect(HDC hdc, int xc, int yc, int R, COLORREF c);
void DrawCirclePolar(HDC hdc, int xc, int yc, int R, COLORREF c);
void DrawCircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF c);
void DrawCircleBresenham(HDC hdc, int xc, int yc, int r, COLORREF c);
void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c);

#endif //INC_2D_DRAWING_CIRCLE_H
