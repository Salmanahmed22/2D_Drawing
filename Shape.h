#pragma once
#include <windows.h>
#include <fstream>
#include <string>

class Shape {
public:
    COLORREF color;
    std::string algorithm;

    virtual void draw(HDC hdc) = 0;
    virtual void saveToFile(std::ofstream& file) = 0;
    virtual void loadFromFile(std::ifstream& file) = 0;
    virtual ~Shape() {}
};
