#pragma once
class Scroll
{
public :
	void Resize(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void Horizontal(HWND hWnd, int yDelta);
	void Vertical(HWND hWnd, int yDelta);
	void End();
	int Get_CurX() const;
	int Get_CurY() const;
	bool isScrolling() const;

private :
	int _xMin = 0;
	int _xMax = 0;
	int _xCurrent = 0;

	int _yMin = 0;
	int _yMax = 0;
	int _yCurrent = 0;

	bool _bScroll = false;
};