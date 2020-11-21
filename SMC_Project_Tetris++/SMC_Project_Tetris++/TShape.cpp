#include "TShape.h"

TShape::TShape()
	: TetrisShape(1, 2, Color::Red)
{
	m_piece_array[(m_centerL + 1) * COLUMNS + (m_centerC - 1)] = 1;
	m_piece_array[(m_centerL + 1) * COLUMNS + m_centerC] = 1;
	m_piece_array[(m_centerL + 1) * COLUMNS + (m_centerC + 1)] = 1;
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
	TetrisShape::Position position;
	auto& [i, j] = position;
	for (i = 0; i < ROWS / 2; i++)
	{
		for (j = i; j < ROWS - i - 1; j++)
		{
			std::optional<int> temp = (*this)[position];
			(*this)[position] = (*this)[{j, ROWS - 1 - i}];
			(*this)[{j, ROWS - 1 - i}] = (*this)[{ROWS - 1 - i, ROWS - 1 - j}];
			(*this)[{ROWS - 1 - i, ROWS - 1 - j}] = (*this)[{ROWS - 1 - j, i}];
			(*this)[{ROWS - 1 - j, i}] = temp;
		}
	}
}

void TShape::ScaleUp()
{
	if (!(*this)[{3,2}].has_value())
	{
		(*this)[{0, 2}] = 1;
		(*this)[{2, 0}] = 1;
		(*this)[{2, 4}] = 1;
	}
	if (!(*this)[{2,3}].has_value())
	{
		(*this)[{0, 2}] = 1;
		(*this)[{2, 0}] = 1;
		(*this)[{4, 2}] = 1;
	}
	if (!(*this)[{1, 2}].has_value())
	{
		(*this)[{2, 0}] = 1;
		(*this)[{4, 2}] = 1;
		(*this)[{2, 4}] = 1;
	}
	if (!(*this)[{2, 1}].has_value())
	{
		(*this)[{0, 2}] = 1;
		(*this)[{2, 4}] = 1;
		(*this)[{4, 2}] = 1;
	}
}

void TShape::ScaleDown()
{
	if ((*this)[{0,2}].has_value() && (*this)[{2,0}].has_value() && (*this)[{2,4}].has_value())
	{
		(*this)[{0, 2}].reset();
		(*this)[{2, 0}].reset();
		(*this)[{2, 4}].reset();
	}
	if ((*this)[{0, 2}].has_value() && (*this)[{2, 0}].has_value() && (*this)[{4, 2}].has_value())
	{
		(*this)[{0, 2}].reset();
		(*this)[{2, 0}].reset();
		(*this)[{4, 2}].reset();
	}
	if ((*this)[{2, 0}].has_value() && (*this)[{4, 2}].has_value() && (*this)[{2, 4}].has_value())
	{
		(*this)[{2, 0}].reset();
		(*this)[{4, 2}].reset();
		(*this)[{2, 4}].reset();
	}
	if ((*this)[{0, 2}].has_value() && (*this)[{2, 4}].has_value() && (*this)[{4, 2}].has_value())
	{
		(*this)[{0, 2}].reset();
		(*this)[{2, 4}].reset();
		(*this)[{4, 2}].reset();
	}
}
