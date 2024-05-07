#pragma once
#define GRID_WIDTH 300
#define GRID_HEIGHT 200
#include "Heap.h"

struct Tile
{
	bool _obstacle = false;
	bool _visited = false;
	double G = 0;   // ������κ��� �Ÿ�
	double H = 0;   // ���������� �Ÿ�
	double F = 0;   // G + H -> key ��
	Position _parant;
};

extern Heap<Position, double> g_OpenList;

extern int GRID_SIZE;
extern Tile g_Tile[][GRID_WIDTH];

extern Position g_start;
extern Position g_end;;

extern bool g_bFind;

Position GetTilePosition(LPARAM lParam);
double CompareF(Position pos1, Position pos2);
bool Find_Path();

