#include "DrawingManager.h"

#include "Circle.h"

void DrawingManager::DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF color) {
    Circle::DrawModifiedMidpoint(hdc, xc, yc, R, color);
}