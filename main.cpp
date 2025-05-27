#include <windows.h>
#include "MenuHandler.h"
#include "Shape.h"
#include <vector>

std::vector<Shape*> shapes;
COLORREF currentColor = RGB(0, 0, 0);
std::string currentAlgorithm = "DDA";

// Global variables
extern std::vector<Shape*> shapes;
extern COLORREF currentColor;
extern std::string currentAlgorithm;

// Function declarations
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

