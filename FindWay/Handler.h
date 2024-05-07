#pragma once
void WCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
void WSize(HWND hWnd, WPARAM wParam, LPARAM lParam);
void WPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
void WDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

void Mouse_L_Down(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_L_DC(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_L_Up(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_R_DC(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_Move(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_Wheel(HWND hWnd, WPARAM wParam, LPARAM lParam);

void Key_Space(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Key_W(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Key_A(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Key_S(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Key_D(HWND hWnd, WPARAM wParam, LPARAM lParam);

extern Scroll g_Scroll;
extern Map g_map;
extern AStar g_Astar;
