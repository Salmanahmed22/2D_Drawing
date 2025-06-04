#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Var&defines.h"
using namespace std;

#ifndef INC_2D_DRAWING_FILLING_H
#define INC_2D_DRAWING_FILLING_H

struct TableEntry {
    int xLeft;
    int xRight;
};
typedef TableEntry Table[1000];

void InitTable(Table t);
void edge2Table(POINT p1, POINT p2, Table t);
void polygonToTable(POINT p[], int n, Table t);
void tableToScreen(HDC hdc, Table t, COLORREF c);
void ConvexFill(HDC hdc, const vector<POINT>& p, COLORREF c);
void FillQuarterLine(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c);
void FillQuarterWithCircles(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c);
void FloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor);
void FloodFillRec(HDC hdc , int x ,int y , COLORREF borderColor, COLORREF fillColor);

#endif //INC_2D_DRAWING_FILLING_H
