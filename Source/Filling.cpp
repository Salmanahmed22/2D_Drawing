#include <Windows.h>
#include <bits/stdc++.h>
#include "../Include/Utils.h"
#include "../Include/Filling.h"
#include "../Include/Curves.h"

using namespace std;

//convex fill

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

//general fill

void InitEdgeTable(edgeTable t){
    for (int i = 0; i < 2000; ++i) {
        t[i].clear();
    }
}

void buildEdgeTable(const vector<POINT>& pts, edgeTable t) {
    for (size_t i = 0; i < pts.size(); ++i) {
        POINT p1 = pts[i];
        POINT p2 = pts[(i + 1) % pts.size()];

        if (p1.y == p2.y) continue;

        int ymin = std::min(p1.y, p2.y);
        int ymax = std::max(p1.y, p2.y);
        float x = (p1.y < p2.y) ? p1.x : p2.x;
        float dx = (float)(p2.x - p1.x) / (p2.y - p1.y);

        Edge e = { x, dx, ymax };
        t[ymin].push_back(e);
    }
}

void scanlineFill(HDC hdc, edgeTable t, COLORREF c) {
    vector<Edge> active;

    HPEN hPen = CreatePen(PS_SOLID, 1, c);
    HBRUSH hBrush = CreateSolidBrush(c);

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    for (int y = 0; y < 2000; ++y) {
        for (auto& e : t[y]) {
            active.push_back(e);
        }

        if (active.empty()) continue;

        sort(active.begin(), active.end(), [](const Edge& a, const Edge& b) {
            return a.x < b.x;
        });

        for (size_t i = 0; i + 1 < active.size(); i += 2) {
            MoveToEx(hdc, (int)round(active[i].x), y, NULL);
            LineTo(hdc, (int)round(active[i + 1].x), y);
        }

        for (auto& e : active) {
            e.x += e.dx;
        }

        active.erase(remove_if(active.begin(), active.end(), [y](const Edge& e) {
            return y + 1 >= e.ymax;
        }), active.end());
    }

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void GeneralFill(HDC hdc, const vector<POINT>& pts, COLORREF c){
    edgeTable t;
    InitEdgeTable(t);
    buildEdgeTable(pts, t);
    scanlineFill(hdc, t, c);
}

//

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
        DrawQuarterCircle(hdc, xc, yc, r1, quarter, c);
    }
}

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

void FloodFillRec(HDC hdc , int x ,int y , COLORREF borderColor, COLORREF fillColor) {
    COLORREF c = GetPixel(hdc, x, y );
    if (c==borderColor || c==fillColor) return;
    SetPixel(hdc,x,y,fillColor);
    FloodFillRec(hdc,x+1,y,borderColor,fillColor);
    FloodFillRec(hdc,x-1,y,borderColor,fillColor);
    FloodFillRec(hdc,x,y+1,borderColor,fillColor);
    FloodFillRec(hdc,x,y-1,borderColor,fillColor);
}

float H1(float t) { return 2 * t * t * t - 3 * t * t + 1; }
float H2(float t) { return -2 * t * t * t + 3 * t * t; }
float H3(float t) { return t * t * t - 2 * t * t + t; }
float H4(float t) { return t * t * t - t * t; }

void DrawHermite(HDC hdc, POINT P0, POINT P1, POINT R0, POINT R1, COLORREF color) {
    for (float t = 0; t <= 1.0f; t += 0.001f) {
        float x = H1(t) * P0.x + H2(t) * P1.x + H3(t) * R0.x + H4(t) * R1.x;
        float y = H1(t) * P0.y + H2(t) * P1.y + H3(t) * R0.y + H4(t) * R1.y;
        SetPixel(hdc, static_cast<int>(x + 0.5f), static_cast<int>(y + 0.5f), color);
    }
}

void FillSquareWithVerticalHermite(HDC hdc, POINT topLeft, int side, POINT R0, POINT R1, COLORREF color) {
    for (int x = 0; x <= side; x += 4) {
        POINT P0 = { topLeft.x + x, topLeft.y };
        POINT P1 = { topLeft.x + x, topLeft.y + side };

        DrawHermite(hdc, P0, P1, R0, R1, color);
    }


}


void FillRectangleWithBezierHorizontal(HDC hdc, int xLeft, int yTop, int width, int height, COLORREF color) {
    int xRight = xLeft + width;
    int yBottom = yTop + height;

    HPEN hPen = CreatePen(PS_SOLID, 1, color);
    HGDIOBJ oldPen = SelectObject(hdc, hPen);

    for (int y = yTop; y <= yBottom; y += 5) {
        POINT P0 = { xLeft, y };
        POINT P1 = { xLeft + width / 3, y + 30 };
        POINT P2 = { xLeft + 2 * width / 3, y - 30 };
        POINT P3 = { xRight, y };

        DrawBezierCurve(hdc, P0, P1, P2, P3);
    }

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
}

// Update rectangle bounds based on 3 points
void ComputeRectangleFromPoints(vector<POINT> BezzierPoints , RECT & rectangleBounds) {
    int minX = std::min({ BezzierPoints[0].x, BezzierPoints[1].x, BezzierPoints[2].x });
    int maxX = std::max({ BezzierPoints[0].x, BezzierPoints[1].x, BezzierPoints[2].x });
    int minY = std::min({ BezzierPoints[0].y, BezzierPoints[1].y, BezzierPoints[2].y });
    int maxY = std::max({ BezzierPoints[0].y, BezzierPoints[1].y, BezzierPoints[2].y });

    rectangleBounds = { minX, minY, maxX, maxY };

}

