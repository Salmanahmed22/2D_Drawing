#pragma once
#include <vector>
#include "Shape.h"

namespace FileManager {
    void saveShapesToFile(const std::vector<Shape*>& shapes, const std::string& filename);
    void loadShapesFromFile(std::vector<Shape*>& shapes, const std::string& filename);
}
