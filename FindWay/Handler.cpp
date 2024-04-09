#include <Windows.h>
#include <windowsx.h>
#include "Render.h"
#include "Heap.h"
#include "Tile.h"

bool g_bDrag = false;
bool g_bErase = false;
bool g_bScroll = false;

int g_xCurrent;
int g_yCurrent;

void WCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Init_Brush();
    Init_Pen();
    Init_DoubleBuffer(hWnd);
}

void WPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    Clear();
    Render();
    Flip(hWnd, &ps);
}

void WDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Destory_Brush();
    Destory_Pen();
    PostQuitMessage(0);
}

void Mouse_L_Down(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = GetTilePosition(lParam);

    g_bDrag = true;
    {
        if (g_Tile[tile_pos._y][tile_pos._x]._obstacle)
            g_bErase = true;
        else
            g_bErase = false;
    }
}

void Mouse_L_Up(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_bDrag = false;
}

void Mouse_L_DC(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = GetTilePosition(lParam);

    g_start._x = tile_pos._x;
    g_start._y = tile_pos._y;

    InvalidateRect(hWnd, nullptr, false);
}

void Mouse_R_DC(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = GetTilePosition(lParam);

    g_end._x = tile_pos._x;
    g_end._y = tile_pos._y;

    InvalidateRect(hWnd, nullptr, false);
}

void Mouse_Move(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = GetTilePosition(lParam);

    if (g_bDrag)
    {
        g_Tile[tile_pos._y][tile_pos._x]._obstacle = !g_bErase;
        InvalidateRect(hWnd, nullptr, false);
    }
}

void Mouse_Wheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int xDelta = 0;
    int yDelta;
    int yNewPos;

    yNewPos = g_yCurrent + 1;

    g_bScroll = true;
    yDelta = yNewPos - g_yCurrent;
    ScrollWindowEx(hWnd, 0, -yDelta, nullptr, nullptr, nullptr, nullptr, SW_INVALIDATE);
    UpdateWindow(hWnd);
}

void Key_Space(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Find_Path();
    InvalidateRect(hWnd, nullptr, false);
}