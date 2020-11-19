#pragma once
#include "TetrisShape.h"

class TShape : public TetrisShape
{
public:
	//TShape(uint16_t, uint16_t);
	TShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void Scale();

private:

};

