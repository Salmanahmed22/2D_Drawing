#pragma once
#include "Shape.h"

class Line : public Shape {
public:
    int x1,y1,x2,y2;

    Line(int x1,int y1,int x2,int y2, COLORREF col, std::string algo);
    void draw(HDC hdc) override;
    void saveToFile(std::ofstream& file) override;
    void loadFromFile(std::ifstream& file) override;
};
