#pragma once
#include "Position.h"
#include "Heap.h"

class AStar
{
private :
	struct Tile
	{
		bool _obstacle = false;
		bool _visited = false;
		double G = 0;   // 출발지로부터 거리
		double H = 0;   // 목적지와의 거리
		double F = 0;   // G + H -> key 값
		Position _parent;
	};

	double GetH(int x, int y) const;
	double GetF(int x, int y) const;
	bool CheckPos(int x, int y) const;
	void TileReset();

public : 
	AStar(int width, int height);
	bool Find_Path();

	Position Get_Start() const;
	void Set_Start(int x, int y);
	void Set_Start(Position pos);

	Position Get_End() const;
	void Set_End(int x, int y);
	void Set_End(Position pos);
	

private :
	Tile** _map;
	int _width;
	int _height;

	Position _start;
	Position _end;

	Heap<Position, double> _open_list;
	bool _bFind = false;
	bool _bFinding = false;
};
