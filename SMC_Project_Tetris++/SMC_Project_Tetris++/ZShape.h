#pragma once
#include "TetrisShape.h"
class ZShape :
	public TetrisShape
{
public:
	ZShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void ScaleUp();
	void ScaleDown();
private:

};

