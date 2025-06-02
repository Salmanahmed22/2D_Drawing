#include "Algorithms.h"
#include "Utils.h"
#include <bits/stdc++.h>
using namespace std;

struct TableEntry {
    int xLeft;
    int xRight;
};
typedef TableEntry Table[1000];

//Circle

//mid point circle
void DrawCircleBres(HDC hdc, int xc, int yc, int r, COLORREF c) {
    int x = 0, y = r;
    int d = 1 - r;
    Utils::Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        Utils::Draw8Points(hdc, xc, yc, x, y, c);
    }
}


//modified mid point
void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    int d = 1 - R;
    int d1 = 3, d2 = 5 - 2 * R;
    Utils::Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += d1;
            d2 += 2;
            x++;
        } else {
            d += d2;
            d2 += 4;
            x++;
            y--;
        }
        d1 += 2;
        Utils::Draw8Points(hdc, xc, yc, x, y, c);
    }
}


//Ellipse
void DrawEllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    // calc y from x from -a to a
    for (int x = -a; x <= a; x++) {
        double y = b * sqrt(1.0 - (double)(x * x) / (a * a));
        int ry = Utils::Round(y);
        SetPixel(hdc, xc + x, yc + ry, c);
        SetPixel(hdc, xc + x, yc - ry, c);
    }

    // calc x from y from -b to b
    for (int y = -b; y <= b; y++) {
        double x = a * sqrt(1.0 - (double)(y * y) / (b * b));
        int rx = Utils::Round(x);
        SetPixel(hdc, xc + rx, yc + y, c);
        SetPixel(hdc, xc - rx, yc + y, c);
    }
}

//Line
void drawParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int alpha1 = x2 - x1, alpha2 = y2 - y1;

    float step = 1.0 / max(abs(alpha1),abs(alpha2));

    for (float t = 0.0; t <= 1.0; t+=step) {
        float x = float (alpha1)*t + x1;
        float y = float(alpha2)*t + y1;
        SetPixel(hdc, Utils::Round(x), Utils::Round(y),c);
    }
}

// mid point line
void DrawLineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    SetPixel(hdc, x, y, c);
    if (dx > dy) // slope <= 1
    {
        int d = -2 * dy + dx;
        int d1 = -2 * dy;
        int d2 = 2 * (dx - dy);
        while (x != x2)
        {
            if (d < 0)
            {
                d += d2;
                x += sx;
                y += sy;
            }
            else
            {
                d += d1;
                x += sx;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else // slope > 1
    {
        int d = -2 * dx + dy;
        int d1 = -2 * dx;
        int d2 = 2 * (dy - dx);
        while (y != y2)
        {
            if (d < 0)
            {
                d += d2;
                y += sy;
                x += sx;
            }
            else
            {
                d += d1;
                y += sy;
            }
            SetPixel(hdc, x, y, c);
        }
    }
}

//Curves

//hermite
void DrawHermiteCurve(HDC hdc , int x1, int y1 , int u1, int v1 , int x2, int y2 , int u2, int v2, COLORREF c){
    int hermiteMatrix[4][4] = {
            { 2, -2,  1,  1 },
            {-3,  3, -2, -1 },
            { 0,  0,  1,  0 },
            { 1,  0,  0,  0 }
    };
    int xc[4] = {x1,x2,u1,u2};
    int yc[4] = {y1,y2,v1,v2};

    double a[4], b[4];

    for (int i = 0; i < 4; i++) {
        a[i] = b[i] = 0;
        for (int j = 0; j < 4; j++) {
            a[i] += hermiteMatrix[i][j] * xc[j];
            b[i] += hermiteMatrix[i][j] * yc[j];
        }
    }

    for (double t = 0; t <= 1; t+=0.001) {
        double x = a[0]*pow(t,3) + a[1]*pow(t,2) + a[2]*t + a[3];
        double y = b[0]*pow(t,3) + b[1]*pow(t,2) + b[2]*t + b[3];
        SetPixel(hdc, Utils::Round(x), Utils::Round(y),c);
    }
}

//bezier

void DrawBezierCurve(HDC hdc, const POINT& P0, const POINT& P1, const POINT& P2, const POINT& P3) {
    POINT alpha, beta, gamma, delta;
    Utils::computeBezierCoefficients(P0, P1, P2, P3, alpha, beta, gamma, delta);

    const int steps = 1000;
    for (int i = 0; i <= steps; ++i) {
        double t = (double)i / steps;
        POINT pt = Utils::bezierPoint(t, alpha, beta, gamma, delta);
        SetPixel(hdc, Utils::Round(pt.x), Utils::Round(pt.y), RGB(255, 0, 0)); // Red pixel
    }
}

//Quarter circle line filling

void FillQuarterLine(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c) {
    int dx = px - xc;
    int dy = py - yc;

    if (dx * dx + dy * dy > r * r) return;

    int quarter = -1;
    if (dx >= 0 && dy <= 0) quarter = 1;     // Q1: Top-right
    else if (dx <= 0 && dy <= 0) quarter = 2; // Q2: Top-left
    else if (dx <= 0 && dy >= 0) quarter = 3; // Q3: Bottom-left
    else if (dx >= 0 && dy >= 0) quarter = 4; // Q4: Bottom-right

    for (int y = -r; y <= r; y++) {
        int x_limit = static_cast<int>(sqrt(r * r - y * y));
        int y_pos = yc + y;

        switch (quarter) {
            case 1:
                if (y <= 0) {
                    for (int x = 0; x <= x_limit; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
            case 2:
                if (y <= 0) {
                    for (int x = -x_limit; x <= 0; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
            case 3:
                if (y >= 0) {
                    for (int x = -x_limit; x <= 0; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
            case 4:
                if (y >= 0) {
                    for (int x = 0; x <= x_limit; x++)
                        SetPixel(hdc, xc + x, y_pos, c);
                }
                break;
        }
    }
}


// fill quarter circle with circles

void FillQuarterWithCircles(HDC hdc, int xc, int yc, int r, int px, int py, COLORREF c) {
    int dx = px - xc;
    int dy = py - yc;

    if (dx * dx + dy * dy > r * r)
        return;

    int quarter = -1;
    if (dx >= 0 && dy <= 0) quarter = 1;
    else if (dx <= 0 && dy <= 0) quarter = 2;
    else if (dx <= 0 && dy >= 0) quarter = 3;
    else if (dx >= 0 && dy >= 0) quarter = 4;

    for (int r1 = r; r1 >= 1; r1--) {
        Utils::DrawQuarterCircle(hdc, xc, yc, r1, quarter, c);
    }
}



//flood fill
void FloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor) {
    stack<POINT> s;
    s.push({ x, y });

    while (!s.empty()) {
        POINT p = s.top();
        s.pop();

        COLORREF current = GetPixel(hdc, p.x, p.y);
        if (current == borderColor || current == fillColor)
            continue;

        SetPixel(hdc, p.x, p.y, fillColor);

        s.push({ p.x + 1, p.y });
        s.push({ p.x - 1, p.y });
        s.push({ p.x, p.y + 1 });
        s.push({ p.x, p.y - 1 });
    }
}

//Recursive Flood Fill
void FloodFillRec(HDC hdc , int x ,int y , COLORREF borderColor, COLORREF fillColor) {
    COLORREF c = GetPixel(hdc, x, y );
    if (c==borderColor || c==fillColor) return;
    SetPixel(hdc,x,y,fillColor);
    FloodFillRec(hdc,x+1,y,borderColor,fillColor);
    FloodFillRec(hdc,x-1,y,borderColor,fillColor);
    FloodFillRec(hdc,x,y+1,borderColor,fillColor);
    FloodFillRec(hdc,x,y-1,borderColor,fillColor);
}

//Cardinal Spline Curve
struct Point2D{
    double x, y;
    Point2D(double x = 0.0, double y = 0.0):x(x),y(y){};
};

void DrawCardinalSpline(HDC hdc, Point2D P[], int n, double c, COLORREF color) {
    if (n < 4) return;
    double s = c/2.0;
    for (int i = 1; i < n - 2; ++i) {
        int T1x = (int)(s * (P[i + 1].x - P[i - 1].x));
        int T1y = (int)(s * (P[i + 1].y - P[i - 1].y));
        int T2x = (int)(s * (P[i + 2].x - P[i].x));
        int T2y = (int)(s * (P[i + 2].y - P[i].y));

        DrawHermiteCurve(
            hdc,
            (int)P[i].x, (int)P[i].y,T1x, T1y,
            (int)P[i + 1].x, (int)P[i + 1].y,T2x, T2y,
            color
        );
    }
}

//line clipping

union outCode {
    struct {
        unsigned l:1, r:1, b:1, t:1;
    };
    unsigned all:4;
};

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

void CohenSutherland(POINT p1, POINT p2, Window window,HDC hdc, COLORREF c) {
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
    if (visible) drawParametricLine(hdc, p1.x, p1.y, p2.x, p2.y, c);
}


//polygon clipping
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
            drawParametricLine(hdc, p1.x, p1.y, p2.x, p2.y, c);
            p1 = p2;
        }
    }
}


// convex filling algorithm
void InitTable(Table t) {
    for (int i = 0; i < 1000; ++i) {
        t[i].xLeft = INT_MAX;
        t[i].xRight = INT_MIN;
    }
}


void edge2Table(POINT p1, POINT p2, Table t) {
    if (p2.y == p1.y) return;
    if (p1.y > p2.y) swap(p1, p2);
    double x = p1.x;
    int y = p1.y;
    double mInv = (double)(p2.x - p1.x) / (p2.y - p1.y);

    while (y < p2.y) {
        if (x < t[y].xLeft) t[y].xLeft = ceil(x);
        if (x > t[y].xRight) t[y].xRight = floor(x);
        y++;
        x += mInv;
    }
}


void polygonToTable(POINT p[], int n, Table t) {
    POINT v1 = p[n - 1];
    for (int i = 0; i < n; ++i) {
        POINT v2 = p[i];
        edge2Table(v1, v2, t);
        v1 = p[i];
    }
}


void tableToScreen(HDC hdc, Table t, COLORREF c) {
    for (int i = 0; i < 1000; ++i) {
        if (t[i].xLeft < t[i].xRight) {
            for (int x = t[i].xLeft; x <= t[i].xRight; ++x) {
                SetPixel(hdc, x, i, c);
            }
        }
    }
}


void ConvexFill(HDC hdc, const vector<POINT>& p, COLORREF c) {
    Table t;
    InitTable(t);
    polygonToTable((POINT*)&p[0], p.size(), t);
    tableToScreen(hdc, t, c);
}