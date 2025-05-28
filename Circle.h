#pragma once
#include <windows.h>
#include "Color.h"
#include <bits/stdc++.h>
class Circle {
    int x,y,xc,yc,R;
public:
    static void DrawModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color);
    int calculateRadius(int x,int y,int xc, int yc){
        return static_cast<int>(sqrt(pow(x-xc,2) + pow(y-yc,2)));
    }
};