#include <windows.h>
#include "MenuHandler.h"
#include "Shape.h"
#include <vector>

std::vector<Shape*> shapes;
COLORREF currentColor = RGB(0, 0, 0);
std::string currentAlgorithm = "DDA";

enum CircleAlgorithm {
    CIRCLE_NONE,
    CIRCLE_DIRECT,
    CIRCLE_POLAR,
    CIRCLE_ITERATIVE_POLAR,
    CIRCLE_MIDPOINT,
    CIRCLE_MODIFIED_MIDPOINT
};

static CircleAlgorithm currentCircleAlgo = CIRCLE_NONE;

// Global variables
extern std::vector<Shape*> shapes;
extern COLORREF currentColor;
extern std::string currentAlgorithm;

// Function declarations
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

