#pragma once
class Mouse
{
public: 
	void Left_Down(int x, int y);
	void Left_Up();
	void Left_Double_Click(int x, int y) const;
	void Right_Double_Click(int x, int y) const;

	void Move(int x, int y) const;

private :
	bool _drag = false;
	bool _erase = false;

};