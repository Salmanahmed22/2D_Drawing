#pragma once
#include <Windows.h>
#include <bits/stdc++.h>
#include "Clipping.h"
using namespace std;

#ifndef VAR_DEFINES_H
#define VAR_DEFINES_H

// Menu Command IDs
#define IDM_BG_WHITE          1
#define IDM_BG_BLACK          2
#define IDM_CURSOR_ARROW      3
#define IDM_CURSOR_CROSS      4
#define IDM_SAVE              5
#define IDM_LOAD              6
#define IDM_CLEAR             7

// Shape Algorithms
#define IDM_LINE_DDA          100
#define IDM_LINE_MIDPOINT     101
#define IDM_LINE_PARAMETRIC   102
#define IDM_CIRCLE_DIRECT     103
#define IDM_CIRCLE_POLAR      104
#define IDM_CIRCLE_ITER_POLAR 105
#define IDM_CIRCLE_MIDPOINT   106
#define IDM_CIRCLE_MOD_MID    107

#define IDM_FILL_CIRCLE_LINES 108
#define IDM_FILL_CIRCLE_CIRC  109
#define IDM_FILL_SQUARE_HERM  110
#define IDM_FILL_RECT_BEZIER  111
#define IDM_FILL_CONVEX       112
#define IDM_FILL_NONCONVEX    113
#define IDM_FLOOD_RECURSIVE   114
#define IDM_FLOOD_NONREC      115
#define IDM_CARDINAL_SPLINE   116
#define IDM_ELLIPSE_DIRECT    117
#define IDM_ELLIPSE_POLAR     118
#define IDM_ELLIPSE_MIDPOINT  119
#define IDM_CLIP_RECT_POINT   120
#define IDM_CLIP_RECT_LINE    121
#define IDM_CLIP_RECT_POLY    122
#define IDM_CLIP_SQUARE_POINT 123
#define IDM_CLIP_SQUARE_LINE  124

#define IDM_COLOR_RED      5001
#define IDM_COLOR_ORANGE   5002
#define IDM_COLOR_YELLOW   5003
#define IDM_COLOR_GREEN    5004
#define IDM_COLOR_BLUE     5005
#define IDM_COLOR_INDIGO   5006
#define IDM_COLOR_VIOLET   5007


struct Vars {
    COLORREF c = RGB(255, 0, 0);
    int currentOption = 0;
    int x1 = 0 , y1 = 0 , x2 = 0 , y2 = 0;
    int xc = 0 , yc = 0 , a = 0 , b = 0;
    int r = 0 , x = 0 , y = 0;
    vector<POINT> convexPoints , nonConvexPoints ;
//    vector<Vector2> splinePoints;
    Window squareWindow = Window(100, 500, 100, 500);
    Window rectangleWindow = Window(100, 700, 100, 500);
    vector<POINT> clipWindowPoints;
    vector<POINT> currentLine;
    vector<POINT> polygonPoints;
    int clickCount = 0;
    POINT squareTopLeft;
    POINT squareBottomRight;
    POINT tangentClickTop;
    POINT tangentClickBottom;
    int squareSize = 0;
    POINT R0,R1;
    bool readyToDraw = false;
    int polygonPointsExpected = 0;
};

#endif //VAR_DEFINES_H


