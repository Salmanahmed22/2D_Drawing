#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Utils.h"
#include "../Include/Clipping.h"
#include "../Include/Line.h"

using namespace std;


outCode getOutcode(POINT p, Window window) {
    outCode res;
    res.all = 0;
    if (p.x < window.leftX) res.l = 1;
    if (p.x > window.rightX) res.r = 1;
    if (p.y < window.bottomY) res.b = 1;
    if (p.y > window.topY) res.t = 1;
    return res;
}

POINT Hintersect(double Xedge, POINT p1, POINT p2) {
    POINT res;
    res.x = Xedge;
    res.y = (p2.y - p1.y) * (Xedge - p1.x) / (p2.x - p1.x) + p1.y;
    return res;
}

POINT Vintersect(double Yedge, POINT p1, POINT p2) {
    POINT res;
    res.y = Yedge;
    res.x = (p2.x - p1.x) * (Yedge - p1.y) / (p2.y - p1.y) + p1.x;
    return res;
}

void CohenSutherland(POINT p1, POINT p2, Window window,HDC hdc, COLORREF c){
    outCode out1 = getOutcode(p1, window);
    outCode out2 = getOutcode(p2, window);
    bool visible = false;

    while (true) {
        if (out1.all == 0 && out2.all == 0) {
            visible = true;
            break;
        }
        if ((out1.all & out2.all) != 0) {
            break;
        }

        if (out1.all != 0) {
            if (out1.l) p1 = Hintersect(window.leftX, p1, p2);
            else if (out1.r) p1 = Hintersect(window.rightX, p1, p2);
            else if (out1.b) p1 = Vintersect(window.bottomY, p1, p2);
            else if (out1.t) p1 = Vintersect(window.topY, p1, p2);
            out1 = getOutcode(p1, window);
        } else {
            if (out2.l) p2 = Hintersect(window.leftX, p1, p2);
            else if (out2.r) p2 = Hintersect(window.rightX, p1, p2);
            else if (out2.b) p2 = Vintersect(window.bottomY, p1, p2);
            else if (out2.t) p2 = Vintersect(window.topY, p1, p2);
            out2 = getOutcode(p2, window);
        }
    }

//    if (visible) return {true, {p1, p2}};
//    else return {false, {p1, p2}};
    if (visible) DrawParametricLine(hdc, p1.x, p1.y, p2.x, p2.y, c);
}

vector<POINT> leftClip(vector<POINT> ps, int Xleft) {
    int n = ps.size();
    POINT p1 = ps[n - 1];
    bool in1 = (p1.x >= Xleft);
    vector<POINT> ret;
    for (int i = 0; i < n; ++i) {
        POINT p2 = ps[i];
        bool in2 = (p2.x >= Xleft);
        if (in1 && in2) ret.push_back(p2);
        else if (in1) ret.push_back(Hintersect(Xleft, p1, p2));
        else if (in2) {
            ret.push_back(Hintersect(Xleft, p1, p2));
            ret.push_back(p2);
        }
        in1 = in2;
        p1 = p2;
    }
    return ret;
}

vector<POINT> rightClip(vector<POINT> ps, int Xright) {
    int n = ps.size();
    POINT p1 = ps[n - 1];
    bool in1 = (p1.x <= Xright);
    vector<POINT> ret;
    for (int i = 0; i < n; ++i) {
        POINT p2 = ps[i];
        bool in2 = (p2.x <= Xright);
        if (in1 && in2) ret.push_back(p2);
        else if (in1) ret.push_back(Hintersect(Xright, p1, p2));
        else if (in2) {
            ret.push_back(Hintersect(Xright, p1, p2));
            ret.push_back(p2);
        }
        in1 = in2;
        p1 = p2;
    }
    return ret;
}

vector<POINT> bottomClip(vector<POINT> ps, int Ybottom) {
    int n = ps.size();
    POINT p1 = ps[n - 1];
    bool in1 = (p1.y >= Ybottom);
    vector<POINT> ret;
    for (int i = 0; i < n; ++i) {
        POINT p2 = ps[i];
        bool in2 = (p2.y >= Ybottom);
        if (in1 && in2) ret.push_back(p2);
        else if (in1) ret.push_back(Vintersect(Ybottom, p1, p2));
        else if (in2) {
            ret.push_back(Vintersect(Ybottom, p1, p2));
            ret.push_back(p2);
        }
        in1 = in2;
        p1 = p2;
    }
    return ret;
}

vector<POINT> topClip(vector<POINT> ps, int Ytop) {
    int n = ps.size();
    POINT p1 = ps[n - 1];
    bool in1 = (p1.y <= Ytop);
    vector<POINT> ret;
    for (int i = 0; i < n; ++i) {
        POINT p2 = ps[i];
        bool in2 = (p2.y <= Ytop);
        if (in1 && in2) ret.push_back(p2);
        else if (in1) ret.push_back(Vintersect(Ytop, p1, p2));
        else if (in2) {
            ret.push_back(Vintersect(Ytop, p1, p2));
            ret.push_back(p2);
        }
        in1 = in2;
        p1 = p2;
    }
    return ret;
}

void polygonClipping(HDC hdc, vector<POINT> ps, Window window, COLORREF c) {
    vector<POINT> p1 = leftClip(ps, window.leftX);
    vector<POINT> p2 = topClip(p1, window.topY);
    vector<POINT> p3 = rightClip(p2, window.rightX);
    vector<POINT> res = bottomClip(p3, window.bottomY);

    if (!res.empty()) {
        POINT p1 = res[res.size() - 1];
        for (int i = 0; i < res.size(); ++i) {
            POINT p2 = res[i];
            DrawParametricLine(hdc, p1.x, p1.y, p2.x, p2.y, c);
            p1 = p2;
        }
    }
}

void drawWindow(Window window, HDC hdc, COLORREF c){
    for (int i = window.bottomY; i <= window.topY; ++i) {
        SetPixel(hdc,window.leftX,i,c);
        SetPixel(hdc,window.rightX,i,c);
    }
    for (int i = window.leftX; i <= window.rightX; ++i) {
        SetPixel(hdc,i,window.topY,c);
        SetPixel(hdc,i,window.bottomY,c);
    }
}

bool pointClipping(POINT p, Window window){
    return (p.x >= window.leftX and p.x <= window.rightX and p.y >= window.bottomY and p.y <= window.topY);
}