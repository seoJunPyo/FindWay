#pragma once
void Init_Brush();
void Init_Pen();
void Destory_Pen();
void Destory_Brush();
void Init_DoubleBuffer(HWND hWnd);
void Clear();
void Render();
void Flip(HWND hWnd, PAINTSTRUCT* ps);