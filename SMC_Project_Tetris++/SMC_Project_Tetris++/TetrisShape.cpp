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
	return m_ID;
}

std::array<TetrisShape::Position, 4> TetrisShape::GetBlockPosition() const
{
	std::array<Position, 4> blockPosition;
	for (int i = 0; i < 4; i++)
	{
		blockPosition[i] = Position{ m_Block[i].x + m_Position.x, m_Block[i].y + m_Position.y };
	}
	return blockPosition;
}

std::array<TetrisShape::Position, 4> TetrisShape::GetFutureBlockPosition(Direction direction) const
{
	std::array<Position, 4> blockPositions;
	Position tempPosition{ m_Position };

	if (direction == Direction::Left)
		tempPosition.x--;
	else if (direction == Direction::Right)
		tempPosition.x++;
	else
		tempPosition.y++;

	for (auto i = 0; i < 4; ++i) {
		blockPositions[i] = Position{ m_Block[i].x + tempPosition.x, m_Block[i].y + tempPosition.y };
	}
	return blockPositions;
}

void TetrisShape::RevertState()
{
	m_Block = m_OldBlock;
}

void TetrisShape::SetPosition(const Position& position)
{
	m_Position = position;
}

void TetrisShape::Rotate()
{
	m_OldBlock = m_Block; //store state of Block in case rotation turns out to be invalid

	if (m_ID == 0) { //SquareShape: does not need rotation
		return;
	}
	if (m_ID == 6) { // IShape: restrict "rotation" to two states (horizontal/vertical)
		m_CurrentRotation++;
		for (auto i = 0; i < 4; ++i) {
			Position oldPoint = m_Block[i];    //pivot
			Position localVector = oldPoint - Position{ 1, 2 };
			Position nextPoint{};
			if (m_CurrentRotation % 2 == 1) {
				/* counter-clockwise
				 * [0  -1]
				 * [-1  0]*/
				nextPoint = Position{ (0 * localVector.x) + (-1 * localVector.y),
										 (1 * localVector.x) + (0 * localVector.y) };

			}
			else {

				nextPoint = Position{ (0 * localVector.x) + (1 * localVector.y),
										 (-1 * localVector.x) + (0 * localVector.y) };

			}
			m_Block[i] = Position{ 1,2 } +nextPoint;

		}
		return;
	}
	for (auto i = 0; i < 4; ++i) {
		Position oldPoint = m_Block[i];    //pivot
		Position localVector = oldPoint - Position{ 1,2 };

		/*//Rotation Matrix
		 * [cos Degree    -sin Degree]
		 * [sin Degree     cos Degree]
		 * translates to
		 * clockwise
		 * [0   -1]
		 * [1    0]
		 * */

		Position nextPoint{ (0 * localVector.x) + (-1 * localVector.y),
								(1 * localVector.x) + (0 * localVector.y) };
		m_Block[i] = Position{ 1,2 } + nextPoint;
	}
}

void TetrisShape::Move(Direction direction)
{
	if (direction == Direction::Left)
		m_Position.x--;
	else if (direction == Direction::Right)
		m_Position.x++;
	else
		m_Position.y++;
}

void TetrisShape::ScaleUp()
{
}

void TetrisShape::ScaleDown()
{
}

void TetrisShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 4; i++)
	{
		m_Sprite.setPosition((m_Block[i].x * 18) + (m_Position.x * 18), (m_Block[i].y * 18) + (m_Position.y * 18));
		target.draw(m_Sprite);
	}
}
