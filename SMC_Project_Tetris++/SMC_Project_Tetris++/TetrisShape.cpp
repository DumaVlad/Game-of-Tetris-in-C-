#include "TetrisShape.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <fstream>


unsigned int BlockArray[7][16];
unsigned int ScaledBlockArray[7][16];

void TetrisShape::Read()
{
	std::ifstream readFile("input.txt");
	if (readFile.is_open())
	{
		for (int index = 0; index < 7; index++)
			for (int index1 = 0; index1 < 16; index1++)
				readFile >> BlockArray[index][index1];
		for (int index = 0; index < 7; index++)
			for (int index1 = 0; index1 < 16; index1++)
				readFile >> ScaledBlockArray[index][index1];
	}
	else
		std::cout << "File was not open!";
}

TetrisShape::TetrisShape(sf::Texture& texture, uint16_t id, Position start)
	: m_Position{ start }, m_CurrentRotation{ 0 }, m_ID{ id }, m_Block{}, m_Sprite{ texture, sf::IntRect{(id % 7) * 18, 0, 18, 18} }
{
	Read();
	m_ID = m_ID % 7; // In case of an id > 6, we make sure that is not out of bounds
	for (int index = 0; index < 16; index++)
	{
		m_Block[index].x = BlockArray[m_ID][index] % 8;
		m_Block[index].y = BlockArray[m_ID][index] / 8;
	}
}

uint16_t TetrisShape::GetID() const
{
	return m_ID;
}

std::array<TetrisShape::Position, 16> TetrisShape::GetBlockPosition() const
{
	std::array<Position, 16> blockPosition;
	for (int i = 0; i < 16; i++)
	{
		blockPosition[i] = Position{ m_Block[i].x + m_Position.x, m_Block[i].y + m_Position.y };
	}
	return blockPosition;
}

std::array<TetrisShape::Position, 16> TetrisShape::GetFutureBlockPosition(Direction direction) const
{
	std::array<Position, 16> blockPositions;
	Position tempPosition{ m_Position };

	if (direction == Direction::Left)
		tempPosition.x--;
	else if (direction == Direction::Right)
		tempPosition.x++;
	else
		tempPosition.y++;

	for (auto i = 0; i < 16; ++i) {
		blockPositions[i] = Position{ m_Block[i].x + tempPosition.x, m_Block[i].y + tempPosition.y };
	}
	return blockPositions;
}

void TetrisShape::SetPosition(const Position& position)
{
	m_Position = position;
}

void TetrisShape::Rotate()
{
	if (m_ID == 0) { //SquareShape: does not need rotation
		return;
	}
	if (m_ID == 6) { // IShape: restrict "rotation" to two states (horizontal/vertical)
		m_CurrentRotation++;
		for (auto i = 0; i < 16; ++i) {
			Position oldPoint = m_Block[i];    //pivot
			Position localVector = oldPoint - Position{ 1, 2 };
			Position nextPoint{};
			if (m_CurrentRotation % 2 == 1) {
				nextPoint = Position{ (0 * localVector.x) + (-1 * localVector.y),
										 (1 * localVector.x) + (0 * localVector.y) };

			}
			else {

				nextPoint = Position{ (0 * localVector.x) + (1 * localVector.y),
										 (-1 * localVector.x) + (0 * localVector.y) };

			}
			m_Block[i] = Position{ 1,2 } + nextPoint;

		}
		return;
	}
	for (auto i = 0; i < 16; ++i) {
		Position oldPoint = m_Block[i];    //pivot
		Position localVector = oldPoint - Position{ 1,2 };

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
	for (int i = 0; i < 16; i++)
	{
		m_Block[i].x = ScaledBlockArray[m_ID][i] % 8;
		m_Block[i].y = ScaledBlockArray[m_ID][i] / 8;
	}
}

void TetrisShape::ScaleDown()
{
	for (int i = 0; i < 16; i++)
	{
		m_Block[i].x = BlockArray[m_ID][i] % 8;
		m_Block[i].y = BlockArray[m_ID][i] / 8;
	}
}

void TetrisShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 16; i++)
	{
		m_Sprite.setPosition((m_Block[i].x * 18) + (m_Position.x * 18), (m_Block[i].y * 18) + (m_Position.y * 18));
		target.draw(m_Sprite);
	}
}
