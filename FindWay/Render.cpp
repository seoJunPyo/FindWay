#include <Windows.h>
#include "Heap.h"
#include "Tile.h"
#include "Handler.h"

HPEN g_hGridPen;

HBRUSH g_hObstacleBrush;
HBRUSH g_hStartBrush;
HBRUSH g_hEndBrush;
HBRUSH g_hVisitedBrush;
HBRUSH g_hOtherBrush;

HDC g_hMemDC;
HBITMAP g_hMemDCBitmap;
HBITMAP g_hMemDCBitmap_old;
RECT g_MemDCRect;

void RenderGrid(HDC hdc);
void RenederObstacle(HDC hdc);
void RenderStart(HDC hdc);
void RenderEnd(HDC hdc);
void RenderVisited(HDC hdc);
void RenderPath(HDC hdc);
void RenderOther(HDC hdc);

void Clear()
{
    PatBlt(g_hMemDC, 0, 0, g_MemDCRect.right, g_MemDCRect.bottom, WHITENESS);
}

void Render()
{
    RenderGrid(g_hMemDC);
    RenederObstacle(g_hMemDC);
    RenderVisited(g_hMemDC);
    RenderOther(g_hMemDC);
    RenderStart(g_hMemDC);
    RenderEnd(g_hMemDC);

    if (g_bFind)
        RenderPath(g_hMemDC);
}

void Flip(HWND hWnd, PAINTSTRUCT* ps)
{
    HDC hdc = BeginPaint(hWnd, ps);
    BitBlt(hdc, 0, 0, g_MemDCRect.right, g_MemDCRect.bottom, g_hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, ps);
}

void Init_Pen()
{
    g_hGridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
}

void Init_Brush()
{
    g_hObstacleBrush = CreateSolidBrush(RGB(100, 100, 100));
    g_hStartBrush = CreateSolidBrush(RGB(255, 0, 0));
    g_hEndBrush = CreateSolidBrush(RGB(0, 255, 0));
    g_hVisitedBrush = CreateSolidBrush(RGB(225, 225, 0));
    g_hOtherBrush = CreateSolidBrush(RGB(0, 0, 255));
  
}

void Destory_Pen()
{
    DeleteObject(g_hGridPen);
}

void Destory_Brush()
{
    DeleteObject(g_hObstacleBrush);
}

void Init_DoubleBuffer(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);
    GetClientRect(hWnd, &g_MemDCRect);

    g_hMemDCBitmap = CreateCompatibleBitmap(hdc, g_MemDCRect.right , g_MemDCRect.bottom);
    g_hMemDC = CreateCompatibleDC(hdc);

    ReleaseDC(hWnd, hdc);
    g_hMemDCBitmap_old = (HBITMAP)SelectObject(g_hMemDC, g_hMemDCBitmap);
}

void RenderGrid(HDC hdc)
{
    int iX = 0;
    int iY = 0;

    HPEN hOldPen = (HPEN)SelectObject(hdc, g_hGridPen);

    for (int iCntW = 0; iCntW <= GRID_WIDTH; iCntW++)
    {
        MoveToEx(hdc, iX, 0, nullptr);
        LineTo(hdc, iX, GRID_HEIGHT * GRID_SIZE);
        iX += GRID_SIZE;
    }

    for (int iCntH = 0; iCntH <= GRID_HEIGHT; iCntH++)
    {
        MoveToEx(hdc, 0, iY, nullptr);
        LineTo(hdc, GRID_WIDTH * GRID_SIZE, iY);
        iY += GRID_SIZE;
    }
    SelectObject(hdc, hOldPen);
}

void RenederObstacle(HDC hdc)
{
    int iX = 0;
    int iY = 0;
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, g_hObstacleBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));

    for (int iCntW = 0; iCntW < GRID_WIDTH; iCntW++)
    {
        for (int iCntH = 0; iCntH < GRID_HEIGHT; iCntH++)
        {
            if (g_Tile[iCntH][iCntW]._obstacle)
            {
                iX = iCntW * GRID_SIZE;
                iY = iCntH * GRID_SIZE;

                Rectangle(hdc, iX, iY, iX + GRID_SIZE + 2, iY + GRID_SIZE + 2);
            }
        }
    }
    SelectObject(hdc, hOldBrush);
}

void RenderStart(HDC hdc)
{
    if (g_start._x == -1 && g_start._y == -1)
        return;

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, g_hStartBrush);
    
    int iX = g_start._x * GRID_SIZE;
    int iY = g_start._y * GRID_SIZE;
    Rectangle(hdc, iX, iY, iX + GRID_SIZE + 2, iY + GRID_SIZE + 2);

    SelectObject(hdc, hOldBrush);
}

void RenderEnd(HDC hdc)
{
    if (g_end._x == -1 && g_end._y == -1)
        return;

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, g_hEndBrush);

    int iX = g_end._x * GRID_SIZE;
    int iY = g_end._y * GRID_SIZE;
    Rectangle(hdc, iX, iY, iX + GRID_SIZE + 2, iY + GRID_SIZE + 2);

    SelectObject(hdc, hOldBrush);
}

void RenderVisited(HDC hdc)
{
    int iX = 0;
    int iY = 0;
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, g_hVisitedBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));

    for (int iCntW = 0; iCntW < GRID_WIDTH; iCntW++)
    {
        for (int iCntH = 0; iCntH < GRID_HEIGHT; iCntH++)
        {
            if (g_Tile[iCntH][iCntW]._visited)
            {
                iX = iCntW * GRID_SIZE;
                iY = iCntH * GRID_SIZE;

                Rectangle(hdc, iX, iY, iX + GRID_SIZE + 2, iY + GRID_SIZE + 2);
            }
        }
    }
    SelectObject(hdc, hOldBrush);
}

void RenderPath(HDC hdc)
{
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, g_hStartBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));

    Position cur = g_end;

    while (!(cur._x == g_start._x && cur._y == g_start._y))
    {
        int iX = cur._x * GRID_SIZE;
        int iY = cur._y * GRID_SIZE;

        Rectangle(hdc, iX, iY, iX + GRID_SIZE + 2, iY + GRID_SIZE + 2);

        cur = g_Tile[cur._y][cur._x]._parant;
    }
    SelectObject(hdc, hOldBrush);
}

void RenderOther(HDC hdc)
{
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, g_hOtherBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));

    for (int i = 0; i < g_OpenList.getSize(); i++)
    {
        Position pos = g_OpenList[i];

        int iX = pos._x * GRID_SIZE;
        int iY = pos._y * GRID_SIZE;

        Rectangle(hdc, iX, iY, iX + GRID_SIZE + 2, iY + GRID_SIZE + 2);
    }
    SelectObject(hdc, hOldBrush);
}
