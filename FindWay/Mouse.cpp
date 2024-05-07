#include <Windows.h>
#include "Scroll.h"
#include "Position.h"
#include "Map.h"
#include "AStar.h"
#include "Handler.h"
#include "Mouse.h"

inline Position Tile_Position(int x, int y);

inline Position Tile_Position(int x, int y)
{
	return g_map.Get_Tile_Position(x + g_Scroll.Get_CurX(), y + g_Scroll.Get_CurY());
}

void Mouse::Left_Down(int x, int y)
{
    Position tile_pos = Tile_Position(x, y);

    _drag = true;
    {
        if (g_map.isObstacle(tile_pos))
            _erase = true;
        else
            _erase = false;
    }
}

void Mouse::Left_Up()
{
    _drag = false;
}

void Mouse::Left_Double_Click(int x, int y) const
{
    Position tile_pos = Tile_Position(x, y);

    if (g_map.isObstacle(tile_pos))
        return;

    g_Astar.Set_Start(tile_pos);
}

void Mouse::Right_Double_Click(int x, int y) const
{
    Position tile_pos = Tile_Position(x, y);

    if (g_map.isObstacle(tile_pos))
        return;

    g_Astar.Set_End(tile_pos);
}

void Mouse::Move(int x, int y) const
{
    Position tile_pos = Tile_Position(x, y);

    if (_drag)
        g_map.Set_Obstacle(tile_pos);
}