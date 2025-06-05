#include <Windows.h>
#include <bits/stdc++.h>
#include "Var&defines.h"

using namespace std;

#ifndef INC_2D_DRAWING_HANDLE_BUTTONS_H
#define INC_2D_DRAWING_HANDLE_BUTTONS_H


Vars vars;

HMENU SetupMenus();
void HandleChoice(HBRUSH hBackgroundBrush, HCURSOR hCurrentCursor,HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars);
void HandleLeftButtonUP(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars);
void HandleLeftButtonDOWN(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars);
void HandleRightButtonDOWN(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , Vars &vars);

#endif //INC_2D_DRAWING_HANDLE_BUTTONS_H
