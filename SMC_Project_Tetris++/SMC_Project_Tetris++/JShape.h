#pragma once
#include "TetrisShape.h"

class JShape : public TetrisShape
{
public:
	JShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void ScaleUp();
	void ScaleDown();

private:

};
