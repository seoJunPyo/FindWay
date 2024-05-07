#include "AStar.h"
#include <math.h>
#include <malloc.h>

int xD[] = { 0, 1, 1, 1, 0, -1 ,-1, -1 };
int yD[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

AStar::AStar(int width, int height) :_width(width), _height(height)
{
	_map = (Tile**)malloc(sizeof(Tile*) * height);
	_map[0] = (Tile*)malloc(sizeof(Tile) * width * height);

	for (int i = 1; i < height; i++)
		_map[i] = _map[i - 1] + width;
}

Position AStar::Get_Start() const
{
    return _start;
}

void AStar::Set_Start(int x, int y)
{
    _start._x = x;
    _start._y = y;
}

void AStar::Set_Start(Position pos)
{
    _start = pos;
}

Position AStar::Get_End() const
{
    return _end;
}

void AStar::Set_End(int x, int y)
{
    _end._x = x;
    _end._y = y;
}

void AStar::Set_End(Position pos)
{
    _end = pos;
}

bool AStar::Find_Path()
{
    if (!_bFinding)
    {
        _open_list.reset();
        TileReset();

        _map[_start._y][_start._x]._visited = true;
        _map[_start._y][_start._x].G = 0;
        _map[_start._y][_start._x].H = GetH(_start._x, _start._y);
        _map[_start._y][_start._x].F = GetF(_start._x, _start._y);

        _open_list.Insert(_start, _map[_start._y][_start._x].F);
        _bFinding = true;
        _bFind = false;
    }


    while (1)
    {
        if (_open_list.isEmpty())
            return false;

        Position front;
        _open_list.DeleteMin(&front);

        if (front._x == _end._x && front._y == _end._y)
        {
            // 찾은 경로를 저장한다.

            _bFind = true;
            _bFinding = false;
            break;
        }

        for (int i = 0; i < 8; i++)
        {
            int x = front._x + xD[i];
            int y = front._y + yD[i];

            if (CheckPos(x, y))
            {
                _map[y][x]._parent = front;
                _map[y][x]._visited = true;

                if (xD[i] == 0 || yD[i] == 0)
                    _map[y][x].G = _map[front._y][front._x].G + 1;
                else
                    _map[y][x].G = _map[front._y][front._x].G + 1.5;

                _map[y][x].H = GetH(x, y);
                _map[y][x].F = GetF(x, y);

                _open_list.Insert(Position{ x, y }, _map[y][x].F);
            }

            for (int i = 0; i < _open_list.getSize(); i++)
            {
                Position cur = _open_list[i];
                if (cur._x == x && cur._y == y)
                {
                    Position parent = _map[y][x]._parent;
                    if (_map[parent._y][parent._x].G > _map[front._y][front._x].G)
                    {
                        _open_list.Delete(i);

                        _map[y][x]._parent = front;
                        _map[y][x]._visited = true;

                        if (xD[i] == 0 || yD[i] == 0)
                            _map[y][x].G = _map[front._y][front._x].G + 1;
                        else
                            _map[y][x].G = _map[front._y][front._x].G + 1.5;

                        _map[y][x].H = GetH(x, y);
                        _map[y][x].F = GetF(x, y);

                        _open_list.Insert(Position{ x, y }, _map[y][x].F);
                    }

                    break;
                }
            }
        }
    }
    
    return true;
}


void AStar::TileReset()
{
    for (int i = 0; i < _height; i++)
        for (int j = 0; j < _width; j++)
            _map[i][j]._visited = false;
}

double AStar::GetH(int x, int y) const
{
    return (abs(x - _end._x) + abs(y - _end._y));
}

double AStar::GetF(int x, int y) const
{
    return _map[y][x].G + _map[y][x].H;
}

bool AStar::CheckPos(int x, int y) const
{
    if (x < 0 || x >= _width || y < 0 || y >= _height)
        return false;

    if (_map[y][x]._obstacle)
        return false;

    if (_map[y][x]._visited)
        return false;

    return true;
}