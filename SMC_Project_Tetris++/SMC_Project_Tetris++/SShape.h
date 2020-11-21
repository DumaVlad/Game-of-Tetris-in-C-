#pragma once
#include "TetrisShape.h"
class SShape :
	public TetrisShape
{
public:
	SShape();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void ScaleUp();
	void ScaleDown();
private: 

};

