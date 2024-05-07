#include <Windows.h>
#include <windowsx.h>
#include <cmath>
#include "Position.h"
#include "Heap.h"
#include "Tile.h"
#include "Scroll.h"
#include "AStar.h"
#include "Handler.h"

Heap<Position, double> g_OpenList;

int GRID_SIZE = 32;
Tile g_Tile[GRID_HEIGHT][GRID_WIDTH];

Position g_start;
Position g_end;

bool g_bFind = false;
bool g_bFinding = false;

int xD[] = { 0, 1, 1, 1, 0, -1 ,-1, -1 };
int yD[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

double GetH(int x, int y);
double GetF(int x, int y);
bool CheckPos(int x, int y);

Position GetTilePosition(LPARAM lParam)
{
    int xPos = GET_X_LPARAM(lParam) + g_Scroll.Get_CurX();
    int yPos = GET_Y_LPARAM(lParam) + g_Scroll.Get_CurY();
    int iTileX = xPos / GRID_SIZE;
    int iTileY = yPos / GRID_SIZE;

    return Position{ iTileX, iTileY };
}

void TileReset()
{
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            g_Tile[i][j]._visited = false;
}

double CompareF(Position pos1, Position pos2)
{
    return g_Tile[pos1._y][pos1._x].F - g_Tile[pos2._y][pos2._x].F;
}

bool Find_Path()
{
    if (!g_bFinding)
    {
        g_OpenList.reset();
        TileReset();

        g_Tile[g_start._y][g_start._x]._visited = true;
        g_Tile[g_start._y][g_start._x].G = 0;
        g_Tile[g_start._y][g_start._x].H = GetH(g_start._x, g_start._y);
        g_Tile[g_start._y][g_start._x].F = GetF(g_start._x, g_start._y);

        g_OpenList.Insert(g_start, g_Tile[g_start._y][g_start._x].F);
        g_bFinding = true;
        g_bFind = false;
    }

    if (g_OpenList.isEmpty())
        return false;

    Position front; 
    g_OpenList.DeleteMin(&front);

    if (front._x == g_end._x && front._y == g_end._y)
    {
        g_bFind = true;
        g_bFinding = false;
        return false;
    }


    for (int i = 0; i < 8; i++)
    {
        int x = front._x + xD[i]; 
        int y = front._y + yD[i];

        if (CheckPos(x, y))
        {
            g_Tile[y][x]._parant = front;
            g_Tile[y][x]._visited = true;

            if (xD[i] == 0 || yD[i] == 0)
                g_Tile[y][x].G = g_Tile[front._y][front._x].G + 1;
            else
                g_Tile[y][x].G = g_Tile[front._y][front._x].G + 1.5;

            g_Tile[y][x].H = GetH(x, y);
            g_Tile[y][x].F = GetF(x, y);

            g_OpenList.Insert(Position{ x, y }, g_Tile[y][x].F);
        }

        for (int i = 0; i < g_OpenList.getSize(); i++)
        {
            Position cur = g_OpenList[i];
            if (cur._x == x && cur._y == y)
            {
                Position parent = g_Tile[y][x]._parant;
                if (g_Tile[parent._y][parent._x].G > g_Tile[front._y][front._x].G)
                {
                    g_OpenList.Delete(i);

                    g_Tile[y][x]._parant = front;
                    g_Tile[y][x]._visited = true;

                    if (xD[i] == 0 || yD[i] == 0)
                        g_Tile[y][x].G = g_Tile[front._y][front._x].G + 1;
                    else
                        g_Tile[y][x].G = g_Tile[front._y][front._x].G + 1.5;

                    g_Tile[y][x].H = GetH(x, y);
                    g_Tile[y][x].F = GetF(x, y);

                    g_OpenList.Insert(Position{ x, y }, g_Tile[y][x].F);
                }

                break;
            }
        }
    }

    return true;
}

double GetH(int x, int y)
{
    return (abs(x - g_end._x) + abs(y - g_end._y));
}

double GetF(int x, int y)
{
    return g_Tile[y][x].G + g_Tile[y][x].H;
}

bool CheckPos(int x, int y)
{
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return false;

    if (g_Tile[y][x]._obstacle)
        return false;

    if (g_Tile[y][x]._visited)
        return false;

    return true;
}
