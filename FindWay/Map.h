#pragma once
#define GRID_WIDTH 300
#define GRID_HEIGHT 200
#define MAX_GRID_SIZE 32

class Map
{
public :
	Map(int size = 16) : _width(GRID_WIDTH), _heigh(GRID_HEIGHT), _grid_size(size) {};

	Position Get_Tile_Position(int xPos, int yPos) const;

	bool isObstacle(int x, int y) const;
	bool isObstacle(Position pos) const;

	void Set_Obstacle(int x, int y);
	void Set_Obstacle(Position pos);
	void Set_Grid_Size(int size);

private :
	bool _map[GRID_HEIGHT][GRID_WIDTH] = { false, };
	int _width;
	int _heigh;
	int _grid_size;
};