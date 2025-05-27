#pragma once
#include <windows.h>

extern COLORREF currentColor;
extern std::string currentAlgorithm;

enum MenuIDs {
    ID_COLOR_RED = 1,
    ID_COLOR_BLUE,
    ID_ALGO_DDA,
    ID_ALGO_MIDPOINT,
    ID_CLEAR_SCREEN,
    ID_SAVE,
    ID_LOAD,
    // ... more as needed
};
