#pragma once
void Init_Brush();
void Init_Pen();
void Destory_Pen();
void Destory_Brush();
void Init_DoubleBuffer(HWND hWnd);
void Render();
void Flip(HWND hWnd, PAINTSTRUCT* ps);

extern HDC g_hMemDC;
extern HBITMAP g_hMemDCBitmap;
extern HBITMAP g_hMemDCBitmap_old;
extern RECT g_MemDCRect;