#pragma once
#define GRID_WIDTH 300
#define GRID_HEIGHT 200
#include "Heap.h"

struct Tile
{
	bool _obstacle = false;
	bool _visited = false;
	double G = 0;   // 출발지로부터 거리
	double H = 0;   // 목적지와의 거리
	double F = 0;   // G + H -> key 값
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

