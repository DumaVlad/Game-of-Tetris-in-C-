#include "TetrisShape.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

/*BlockArray5x5 // The 5x5 array used to store a Shape
[0, 1, 2, 3, 4]
[5, 6, 7, 8, 9]
[10, 11, 12, 13, 14]
[15, 16, 17, 18, 19]
[20, 21, 22, 23, 24]
*/

unsigned int BlockArray5x5[7][4] = {
	{6, 7, 11, 12},   // SquareShape
	{7, 12, 17, 18},  // LShape
	{7, 12, 17, 16},  // JShape
	{6, 11, 12, 17},  // SShape
	{7, 12, 11, 16},  // ZShape
	{7, 11, 12, 13},  // TShape
	{7, 12, 17, 22}   // IShape
};

TetrisShape::TetrisShape(sf::Texture& texture, uint16_t id)
	: m_Position{Position{5,5}}, m_CurrentRotation{0}, m_ID{id}, m_Block{}, m_Sprite{texture, sf::IntRect{(id % 7) * 18, 0, 18, 18}}
{
	m_ID = m_ID % 7; // In case of an id > 6, we make sure that is not out of bounds
	for (int index = 0; index < 4; index++)
	{
		m_Block[index].x = BlockArray5x5[m_ID][index] % 5;
		m_Block[index].y = BlockArray5x5[m_ID][index] / 5;
	}
}

uint16_t TetrisShape::GetID() const
{
	return uint16_t();
}

std::array<TetrisShape::Position, 4> TetrisShape::GetBlockPosition() const
{
	return std::array<Position, 4>();
}

std::array<TetrisShape::Position, 4> TetrisShape::GetFutureBlockPosition(Direction direction) const
{
	return std::array<Position, 4>();
}

void TetrisShape::RevertState()
{
}

void TetrisShape::SetPosition(const Position& position)
{
}

void TetrisShape::Rotate()
{
}

void TetrisShape::Move(Direction direction)
{
}

void TetrisShape::ScaleUp()
{
}

void TetrisShape::ScaleDown()
{
}

void TetrisShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
