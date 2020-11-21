#pragma once
#include "TetrisShape.h"
class IShape : public TetrisShape
{
public:
	IShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void ScaleUp();
	void ScaleDown();
private:

};

