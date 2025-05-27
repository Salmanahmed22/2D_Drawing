#pragma once
#include "Shape.h"

class Line : public Shape {
public:
    POINT p1, p2;

    Line(POINT start, POINT end, COLORREF col, std::string algo);
    void draw(HDC hdc) override;
    void saveToFile(std::ofstream& file) override;
    void loadFromFile(std::ifstream& file) override;
};
