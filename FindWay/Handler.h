#pragma once
void WCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
void WPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
void WDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam);

void Mouse_L_Down(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_L_DC(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_L_Up(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_R_DC(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_Move(HWND hWnd, WPARAM wParam, LPARAM lParam);
void Mouse_Wheel(HWND hWnd, WPARAM wParam, LPARAM lParam);

void Key_Space(HWND hWnd, WPARAM wParam, LPARAM lParam);

extern bool g_bScroll;
extern int g_xCurrent;
extern int g_yCurrent;