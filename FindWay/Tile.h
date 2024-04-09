#pragma once
#define GRID_WIDTH 200
#define GRID_HEIGHT 100

struct Position
{
	int _x = -1;
	int _y = -1;
};

struct Tile
{
	bool _obstacle = false;
	bool _visited = false;
	double G = 0;   // 출발지로부터 거리
	double H = 0;   // 목적지와의 거리
	double F = 0;   // G + H -> key 값
	Position _parant;
};

extern Heap<Position> g_OpenList;

extern int GRID_SIZE;
extern Tile g_Tile[][GRID_WIDTH];

extern Position g_start;
extern Position g_end;;

extern bool g_bFind;

Position GetTilePosition(LPARAM lParam);
double CompareF(Position pos1, Position pos2);
void Find_Path();

