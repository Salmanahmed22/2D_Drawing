#include "Line.h"
#include "DrawingManager.h"

Line::Line(POINT start, POINT end, COLORREF col, std::string algo)
        : p1(start), p2(end) {
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
