#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Var&defines.h"
using namespace std;

#ifndef INC_2D_DRAWING_CLIPPING_H
#define INC_2D_DRAWING_CLIPPING_H


struct Window {
    int leftX, rightX, bottomY, topY;
    Window(int leftX = 0, int rightX = 0, int bottomY = 0, int topY = 0)
            : leftX(leftX), rightX(rightX), bottomY(bottomY), topY(topY) {}
};
union outCode {
    struct {
        unsigned l:1, r:1, b:1, t:1;
    };
    unsigned all:4;
};

outCode getOutcode(POINT p, Window window);
POINT Hintersect(double Xedge, POINT p1, POINT p2);
POINT Vintersect(double Yedge, POINT p1, POINT p2);
void CohenSutherland(POINT p1, POINT p2, Window window,HDC hdc, COLORREF c);
vector<POINT> leftClip(vector<POINT> ps, int Xleft);
vector<POINT> rightClip(vector<POINT> ps, int Xright);
vector<POINT> bottomClip(vector<POINT> ps, int Ybottom);
vector<POINT> topClip(vector<POINT> ps, int Ytop);
void polygonClipping(HDC hdc, vector<POINT> ps, Window window, COLORREF c);
void drawWindow(Window window, HDC hdc, COLORREF c);
#endif //INC_2D_DRAWING_CLIPPING_H
