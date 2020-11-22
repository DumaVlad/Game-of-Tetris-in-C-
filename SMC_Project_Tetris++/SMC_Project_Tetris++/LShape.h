#pragma once
#include "TetrisShape.h"

class LShape : public TetrisShape
{
public:
	LShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void ScaleUp();
	void ScaleDown();

private:

};