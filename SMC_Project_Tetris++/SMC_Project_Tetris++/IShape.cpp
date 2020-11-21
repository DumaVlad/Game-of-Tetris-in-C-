#include "IShape.h"

IShape::IShape()
	: TetrisShape(1, 2, Color::Yellow)
{
	m_piece_array[(m_centerC + 1) * COLUMNS + m_centerL] = 1;
	m_piece_array[(m_centerC + 2) * COLUMNS + m_centerL] = 1;
}

void IShape::MoveLeft()
{
}

void IShape::MoveRight()
{
}

void IShape::MoveDown()
{
}

void IShape::Rotate()
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

void IShape::ScaleUp()
{
	if (!(*this)[{1, 1}].has_value())
	{
		(*this)[{0, 2}] = 1;
		(*this)[{4, 2}] = 1;
	}
	if (!(*this)[{2, 0}].has_value())
	{
		(*this)[{2, 0}] = 1;
		(*this)[{2, 4}] = 1;
	}
}

void IShape::ScaleDown()
{
	if ((*this)[{0, 2}].has_value())
	{
		(*this)[{0, 2}].reset();
		(*this)[{4, 2}].reset();
	}
	if ((*this)[{2, 0}].has_value())
	{
		(*this)[{2, 0}].reset();
		(*this)[{2, 4}].reset();
	}
}
