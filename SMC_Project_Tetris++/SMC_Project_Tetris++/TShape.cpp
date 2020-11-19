#include "TShape.h"

/*TShape::TShape(uint16_t centerL, uint16_t centerC)
	: TetrisShape(centerL,centerC)
{
	m_piece_array[2 * COLUMNS + 1] = 1;
	m_piece_array[2 * COLUMNS + 2] = 1;
	m_piece_array[2 * COLUMNS + 3] = 1;
}*/


TShape::TShape()
	: TetrisShape(1,2)
{
	/*m_piece_array[2, 1] = 1;
	m_piece_array[2, 2] = 1;
	m_piece_array[3, 2] = 1;*/
	m_piece_array[2 * COLUMNS + 1] = 1;
	m_piece_array[2 * COLUMNS + 2] = 1;
	m_piece_array[2 * COLUMNS + 3] = 1;
}

void TShape::MoveLeft()
{
}

void TShape::MoveRight()
{
}

void TShape::MoveDown()
{
}

void TShape::Rotate()
{
}

void TShape::Scale()
{
}
