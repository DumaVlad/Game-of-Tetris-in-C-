#include "SShape.h"

SShape::SShape() : TetrisShape(1, 2, Color::Blue)
{
	m_piece_array[m_centerL * COLUMNS + (m_centerC + 1)] = 1;
	m_piece_array[(m_centerL + 1) * COLUMNS + (m_centerC - 1)] = 1;
	m_piece_array[(m_centerL + 1) * COLUMNS + m_centerC] = 1;
}

void SShape::MoveLeft()
{
}

void SShape::MoveRight()
{
}

void SShape::MoveDown()
{
}

void SShape::Rotate()
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

void SShape::ScaleUp()
{
	if ((*this)[{2, 1}].has_value() && (*this)[{1, 3}].has_value())
	{
		(*this)[{2, 1}].reset();
		(*this)[{3, 1}] = 1;
		(*this)[{3, 2}] = 1;
		(*this)[{3, 0}] = 1;
		(*this)[{1, 4}] = 1;
	}
	if ((*this)[{1, 1}].has_value() && (*this)[{3, 2}].has_value())
	{
		(*this)[{3, 2}].reset();
		(*this)[{0, 1}] = 1;
		(*this)[{2, 3}] = 1;
		(*this)[{3, 3}] = 1;
		(*this)[{4, 3}] = 1;
	}
	if ((*this)[{2, 3}].has_value() && (*this)[{3, 1}].has_value())
	{
		(*this)[{2, 3}].reset();
		(*this)[{3, 0}] = 1;
		(*this)[{1, 2}] = 1;
		(*this)[{1, 3}] = 1;
		(*this)[{1, 4}] = 1;
	}
	if ((*this)[{1, 2}].has_value() && (*this)[{3, 3}].has_value())
	{
		(*this)[{1, 2}].reset();
		(*this)[{2, 1}] = 1;
		(*this)[{1, 1}] = 1;
		(*this)[{0, 1}] = 1;
		(*this)[{4, 3}] = 1;
	}
}

void SShape::ScaleDown()
{
}
