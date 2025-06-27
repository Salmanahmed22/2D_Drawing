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

struct Edge {
    float x;
    float dx;
    int ymax;
};

typedef vector<Edge> edgeTable[2000];

void InitTable(Table t);
void edge2Table(POINT p1, POINT p2, Table t);
void polygonToTable(POINT p[], int n, Table t);
void tableToScreen(HDC hdc, Table t, COLORREF c);
void ConvexFill(HDC hdc, const vector<POINT>& p, COLORREF c);

void InitEdgeTable(edgeTable t);
void buildEdgeTable(const vector<POINT>& pts, edgeTable t);
void scanlineFill(HDC hdc, edgeTable t, COLORREF c);
void GeneralFill(HDC hdc, const vector<POINT>& pts, COLORREF c);


void FillQuarterLine(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c);
void FillQuarterWithCircles(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c);
void FloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor);
void FloodFillRec(HDC hdc , int x ,int y , COLORREF borderColor, COLORREF fillColor);
void FillSquareWithVerticalHermite(HDC hdc, POINT topLeft, int side, POINT R0, POINT R1, COLORREF color);
void FillRectangleWithBezierHorizontal(HDC hdc, int xLeft, int yTop, int width, int height, COLORREF color);
void ComputeRectangleFromPoints(vector<POINT> BezzierPoints , bool & rectangleReady , RECT & rectangleBounds);
#endif //INC_2D_DRAWING_FILLING_H
