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
	double G = 0;   // ������κ��� �Ÿ�
	double H = 0;   // ���������� �Ÿ�
	double F = 0;   // G + H -> key ��
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

