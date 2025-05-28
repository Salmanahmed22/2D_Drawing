#include "Line.h"
#include "DrawingManager.h"

Line::Line(int x1,int y1,int x2,int y2, COLORREF col, std::string algo)
        : x1(x1),y1(y1),x2(x2),y2(y2) {
    color = col;
    algorithm = algo;
}

void Line::draw(HDC hdc) {
    // Call DrawingManager based on algorithm (later)
}

void Line::saveToFile(std::ofstream& file) {
    // Save data (later)
}

void Line::loadFromFile(std::ifstream& file) {
    // Load data (later)
}
