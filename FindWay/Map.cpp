#include "Position.h"
#include "Map.h"

Position Map::Get_Tile_Position(int xPos, int yPos) const
{
	int iTileX = xPos / _grid_size;
	int iTileY = yPos  / _grid_size;

	return Position{ iTileX, iTileY };
}

bool Map::isObstacle(int x, int y) const
{
	return _map[y][x];
}

bool Map::isObstacle(Position pos) const
{
	return _map[pos._y][pos._x];
}

void Map::Set_Obstacle(int x, int y)
{
	_map[y][x] = true;
}

void Map::Set_Obstacle(Position pos)
{
	_map[pos._y][pos._x] = true;
}

void Map::Set_Grid_Size(int size)
{
	if (size >= MAX_GRID_SIZE)
		return;

	_grid_size = size;
}