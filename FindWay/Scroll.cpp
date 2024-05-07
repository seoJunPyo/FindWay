#include <Windows.h>
#include "Scroll.h"
#include "Tile.h"

void Scroll::End()
{
    _bScroll = false;
}

int Scroll::Get_CurX() const
{
    return _xCurrent;
}

int Scroll::Get_CurY() const
{
    return _yCurrent;
}

bool Scroll::isScrolling() const
{
    return _bScroll;
}

void Scroll::Resize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    SCROLLINFO si;

    int xNewSize;
    int yNewSize;

    xNewSize = LOWORD(lParam);
    yNewSize = HIWORD(lParam);

    _xMax= max(GRID_SIZE * GRID_WIDTH - xNewSize, 0);
    _xCurrent = min(_xCurrent, _xMax);
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = _xMin;
    si.nMax = GRID_SIZE * GRID_WIDTH;
    si.nPage = xNewSize;
    si.nPos = _xCurrent;
    SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

    _yMax = max(GRID_SIZE * GRID_HEIGHT - yNewSize, 0);
    _yCurrent = min(_yCurrent, _yMax);
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = _yMin;
    si.nMax = GRID_SIZE * GRID_HEIGHT;
    si.nPage = yNewSize;
    si.nPos = _yCurrent;
    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}

void Scroll::Horizontal(HWND hWnd, int xDelta)
{
    SCROLLINFO si;

    int xNewPos = max(0, _xCurrent + xDelta);
    xNewPos = min(_xMax, xNewPos);

    if (xNewPos == _xCurrent)
        return;

    _bScroll = true;
    _xCurrent = xNewPos;

    ScrollWindowEx(hWnd, -xDelta, 0, (CONST RECT*) NULL,
        (CONST RECT*) NULL, (HRGN)NULL, (PRECT)NULL,
        SW_INVALIDATE);
    UpdateWindow(hWnd);

    si.cbSize = sizeof(si);
    si.fMask = SIF_POS;
    si.nPos = _xCurrent;
    SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
}

void Scroll::Vertical(HWND hWnd, int yDelta)
{
    SCROLLINFO si;

    int yNewPos = max(0, _yCurrent + yDelta);
    yNewPos = min(_yMax, yNewPos);

    if (yNewPos == _yCurrent)
        return;

    _bScroll = true;
    _yCurrent = yNewPos;

    ScrollWindowEx(hWnd, 0, -yDelta, (CONST RECT*) NULL,
        (CONST RECT*) NULL, (HRGN)NULL, (PRECT)NULL,
        SW_INVALIDATE);
    UpdateWindow(hWnd);

    si.cbSize = sizeof(si);
    si.fMask = SIF_POS;
    si.nPos = _yCurrent;
    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}