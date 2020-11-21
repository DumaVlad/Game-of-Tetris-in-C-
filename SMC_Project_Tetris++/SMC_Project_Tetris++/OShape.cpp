#include "OShape.h"

OShape::OShape()
	: TetrisShape(1, 2, Color::Green)
{
	
	m_piece_array[m_centerL * COLUMNS + (m_centerC + 1)] = 1;
	m_piece_array[(m_centerL + 1) * COLUMNS + m_centerC] = 1;
	m_piece_array[(m_centerL + 1) * COLUMNS + (m_centerC + 1)] = 1;
}

void OShape::MoveLeft()
{
}

void OShape::MoveRight()
{
	
}

void OShape::MoveDown()
{
}

void OShape::Roatate()
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

void OShape::ScaleUp()
{
	if (!(*this)[{1, 1}].has_value() && !(*this)[{3, 1}].has_value() && !(*this)[{3, 3}].has_value())
	{
		(*this)[{1, 1}] = 1; 
		(*this)[{2, 1}] = 1;
		(*this)[{3, 1}] = 1;
		(*this)[{3, 2}] = 1;
		(*this)[{3, 3}] = 1;
	}
	if (!(*this)[{1, 3}].has_value() && !(*this)[{3, 3}].has_value() && !(*this)[{3, 1}].has_value())
	{
		(*this)[{1, 3}] = 1;
		(*this)[{2, 3}] = 1;
		(*this)[{3, 3}] = 1;
		(*this)[{3, 2}] = 1;
		(*this)[{3, 1}] = 1;
	}
	if (!(*this)[{1, 1}].has_value() && !(*this)[{1, 3}].has_value() && !(*this)[{3, 3}].has_value())
	{
		(*this)[{1, 1}] = 1;
		(*this)[{1, 2}] = 1;
		(*this)[{1, 3}] = 1;
		(*this)[{2, 3}] = 1;
		(*this)[{3, 3}] = 1;
	}
	if (!(*this)[{1, 3}].has_value() && !(*this)[{1, 1}].has_value() && !(*this)[{3, 1}].has_value())
	{
		(*this)[{1, 3}] = 1; 
		(*this)[{1, 2}] = 1;
		(*this)[{1, 1}] = 1;
		(*this)[{2, 1}] = 1;
		(*this)[{3, 1}] = 1;
	}
}

void OShape::ScaleDown()
{
	if ((*this)[{3, 1}].has_value())
	{
		(*this)[{1, 1}].reset();
		(*this)[{2, 1}].reset();
		(*this)[{3, 1}].reset();
		(*this)[{3, 2}].reset();
		(*this)[{3, 3}].reset();
	}
}
