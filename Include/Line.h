#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Var&defines.h"

#ifndef INC_2D_DRAWING_LINE_H
#define INC_2D_DRAWING_LINE_H

void DrawParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

void DrawLineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

#endif //INC_2D_DRAWING_LINE_H
