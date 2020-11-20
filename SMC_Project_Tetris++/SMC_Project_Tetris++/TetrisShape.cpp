#include "TetrisShape.h"

TetrisShape::TetrisShape()
{
}

TetrisShape::TetrisShape(uint16_t centerL, uint16_t centerC, Color color)
	: m_centerL{centerL}, m_centerC{centerC}, m_color{color}
{
	//m_piece_array[m_centerL,m_centerC] = 1  // nu inteleg de ce nu imi acceseaza operatorul [] 
	m_piece_array[m_centerL * COLUMNS + m_centerC] = 1;
}

TetrisShape::TetrisShape(const TetrisShape& other)
{
	*this = other;
}

TetrisShape::TetrisShape(TetrisShape&& other)
{
	*this = std::move(other);
}

TetrisShape& TetrisShape::operator=(const TetrisShape& other)
{
	if (this != &other)
	{
		m_centerL = other.m_centerL;
		m_centerC = other.m_centerC;
		m_color = other.m_color;
		m_piece_array = other.m_piece_array;
	}
	return *this;
}

TetrisShape& TetrisShape::operator=(TetrisShape&& other)
{
	if (this != &other)
	{
		m_centerL = other.m_centerL;
		m_centerC = other.m_centerC;
		m_color = other.m_color;
		m_piece_array = other.m_piece_array;
	}
	return *this;
}

TetrisShape::~TetrisShape()
{
}

std::optional<int>& TetrisShape::operator[](const Position& position)
{
	const auto& [line, column] = position;
	if (line < ROWS && column < COLUMNS)
		return m_piece_array[line * COLUMNS + column];
	else
		throw "Index out of bounds";
}

const std::optional<int>& TetrisShape::operator[](const Position& position) const
{
	const auto& [line, column] = position;
	if (line < ROWS && column < COLUMNS)
		return m_piece_array[line * COLUMNS + column];
	else
		throw "Index out of bounds";
}

std::ostream& operator<<(std::ostream& outFlux, TetrisShape& shape)
{
	TetrisShape::Position position;
	auto& [line, column] = position;

	for (line = 0; line < TetrisShape::ROWS; line++)
	{
		for (column = 0; column < TetrisShape::COLUMNS ; column++)
		{
			if (const auto& optInt = shape[position]; optInt.has_value())
				outFlux << optInt.value() << " ";
			else
				outFlux << "-" << " ";
		}
		outFlux << std::endl;
	}
	return outFlux;
}
