#include <Windows.h>
#include <windowsx.h>
#include "Render.h"
#include "Heap.h"
#include "Tile.h"
#include "Scroll.h"
#include "Position.h"
#include "Map.h"
#include "AStar.h"

Scroll g_Scroll;
Map g_map;
AStar g_Astar;


bool g_bDrag = false;
bool g_bErase = false;
       
bool g_bSize = false;
 
Position Tile_Position(LPARAM lParam);

Position Tile_Position(LPARAM lParam)
{
    int xPos = GET_X_LPARAM(lParam) + g_Scroll.Get_CurX();
    int yPos = GET_Y_LPARAM(lParam) + g_Scroll.Get_CurY();

    Position tile_pos = g_map.Get_Tile_Position(xPos, yPos);
}

void WCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Init_Brush();
    Init_Pen();
    Init_DoubleBuffer(hWnd);
}

void WSize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
     g_bSize = true; 
     g_Scroll.Resize(hWnd, wParam, lParam);
}

void WPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    PRECT prect;

    int curX = g_Scroll.Get_CurX();
    int curY = g_Scroll.Get_CurY();

    PatBlt(g_hMemDC, 0, 0, GRID_SIZE * GRID_WIDTH, GRID_SIZE * GRID_HEIGHT, WHITENESS);
    Render();

    HDC hdc = BeginPaint(hWnd, &ps);


    if (g_Scroll.isScrolling())
    {
        prect = &ps.rcPaint;

        BitBlt(ps.hdc,
            prect->left, prect->top,
            ((GRID_SIZE * GRID_WIDTH) - prect->left),
            ((GRID_SIZE * GRID_HEIGHT) - prect->top),
            g_hMemDC,
            prect->left + curX,
            prect->top + curY,
            SRCCOPY);

        g_Scroll.End();
    }

    else
    {
        BitBlt(hdc, g_MemDCRect.left, g_MemDCRect.top,
            GRID_SIZE * GRID_WIDTH - g_MemDCRect.left,
            GRID_SIZE * GRID_HEIGHT - g_MemDCRect.top,
            g_hMemDC,
            g_MemDCRect.left + curX,
            g_MemDCRect.top + curY, SRCCOPY);
    }

    EndPaint(hWnd, &ps);
    
}

void WDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Destory_Brush();
    Destory_Pen();
    PostQuitMessage(0);
}

void Mouse_L_Down(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = Tile_Position(lParam);

    g_bDrag = true;
    {
        if (g_map.isObstacle(tile_pos))
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
    Position tile_pos = Tile_Position(lParam);

    g_start._x = tile_pos._x;
    g_start._y = tile_pos._y;

    InvalidateRect(hWnd, nullptr, false);
}

void Mouse_R_DC(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = Tile_Position(lParam);

    g_end._x = tile_pos._x;
    g_end._y = tile_pos._y;

    InvalidateRect(hWnd, nullptr, false);
}

void Mouse_Move(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Position tile_pos = Tile_Position(lParam);

    if (g_bDrag)
    {
        g_Tile[tile_pos._y][tile_pos._x]._obstacle = !g_bErase;
        InvalidateRect(hWnd, nullptr, false);
    }
}

void Key_Space(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    Find_Path();
    InvalidateRect(hWnd, nullptr, false);
}

void Key_W(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_Scroll.Vertical(hWnd,-1);
}

void Key_A(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_Scroll.Horizontal(hWnd, -1);
}

void Key_S(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_Scroll.Vertical(hWnd, 1);
}

void Key_D(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    g_Scroll.Horizontal(hWnd, 1);
}


