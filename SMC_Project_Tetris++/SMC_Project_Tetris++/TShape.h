#pragma once
#include "TetrisShape.h"

class TShape : public TetrisShape
{
public:
	TShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void ScaleUp();
	void ScaleDown();

private:

};

