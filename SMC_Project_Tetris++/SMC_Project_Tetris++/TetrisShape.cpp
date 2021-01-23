#include "TetrisShape.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <fstream>


unsigned int BlockArray[BLOCK_ARRAY_ROWS][BLOCK_ARRAY_COLUMNS];
unsigned int ScaledBlockArray[BLOCK_ARRAY_ROWS][BLOCK_ARRAY_COLUMNS];

void TetrisShape::Read()
{
	std::ifstream readFile("../Resources/Files/inputTetrisShape.txt");
	if (readFile.is_open())
	{
		for (uint16_t index = 0; index < BLOCK_ARRAY_ROWS; index++)
			for (uint16_t index1 = 0; index1 < BLOCK_ARRAY_COLUMNS; index1++)
				readFile >> BlockArray[index][index1];
		for (uint16_t index = 0; index < BLOCK_ARRAY_ROWS; index++)
			for (uint16_t index1 = 0; index1 < BLOCK_ARRAY_COLUMNS; index1++)
				readFile >> ScaledBlockArray[index][index1];
	}
	else
		std::cout << "File was not open!";
}

TetrisShape::TetrisShape(sf::Texture& texture, uint16_t id, Position start)
	: m_position{ start }, m_currentRotation{ 0 }, m_ID{ id }, m_block{}, m_sprite{ texture, sf::IntRect{(id % 7) * 18, 0, 18, 18} }
{
	Read();
	m_ID = m_ID % 7; // In case of an id > 6, we make sure that is not out of bounds
	for (uint16_t index = 0; index < BLOCK_ARRAY_COLUMNS; index++)
	{
		m_block[index].x = BlockArray[m_ID][index] % 8;
		m_block[index].y = BlockArray[m_ID][index] / 8;
	}
}

uint16_t TetrisShape::GetID() const
{
	return m_ID;
}

std::array<TetrisShape::Position, BLOCK_ARRAY_COLUMNS> TetrisShape::GetBlockPosition() const
{
	std::array<Position, BLOCK_ARRAY_COLUMNS> blockPosition;
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		blockPosition[i] = Position{ m_block[i].x + m_position.x, m_block[i].y + m_position.y };
	}
	return blockPosition;
}

std::array<TetrisShape::Position, BLOCK_ARRAY_COLUMNS> TetrisShape::GetFutureBlockPosition(Direction direction) const
{
	std::array<Position, BLOCK_ARRAY_COLUMNS> blockPositions;
	Position tempPosition{ m_position };

	if (direction == Direction::Left)
		tempPosition.x--;
	else if (direction == Direction::Right)
		tempPosition.x++;
	else
		tempPosition.y++;

	for (auto i = 0; i < BLOCK_ARRAY_COLUMNS; ++i) {
		blockPositions[i] = Position{ m_block[i].x + tempPosition.x, m_block[i].y + tempPosition.y };
	}
	return blockPositions;
}

void TetrisShape::SetPosition(const Position& position)
{
	m_position = position;
}

void TetrisShape::Rotate()
{
	if (m_ID == 0) { //SquareShape: does not need rotation
		return;
	}
	if (m_ID == 6) { // IShape: restrict "rotation" to two states (horizontal/vertical)
		m_currentRotation++;
		for (auto i = 0; i < BLOCK_ARRAY_COLUMNS; ++i) {
			Position oldPoint = m_block[i];    //pivot
			Position localVector = oldPoint - Position{ 1, 2 };
			Position nextPoint{};
			if (m_currentRotation % 2 == 1) {
				nextPoint = Position{ (0 * localVector.x) + (-1 * localVector.y),
										 (1 * localVector.x) + (0 * localVector.y) };

			}
			else {

				nextPoint = Position{ (0 * localVector.x) + (1 * localVector.y),
										 (-1 * localVector.x) + (0 * localVector.y) };

			}
			m_block[i] = Position{ 1,2 } + nextPoint;

		}
		return;
	}
	for (auto i = 0; i < BLOCK_ARRAY_COLUMNS; ++i) {
		Position oldPoint = m_block[i];    //pivot
		Position localVector = oldPoint - Position{ 1,2 };

		Position nextPoint{ (0 * localVector.x) + (-1 * localVector.y),
								(1 * localVector.x) + (0 * localVector.y) };
		m_block[i] = Position{ 1,2 } + nextPoint;
	}
}

void TetrisShape::Move(Direction direction)
{
	if (direction == Direction::Left)
		m_position.x--;
	else if (direction == Direction::Right)
		m_position.x++;
	else
		m_position.y++;
}

void TetrisShape::ScaleUp()
{
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		m_block[i].x = ScaledBlockArray[m_ID][i] % 8;
		m_block[i].y = ScaledBlockArray[m_ID][i] / 8;
	}
}

void TetrisShape::ScaleDown()
{
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		m_block[i].x = BlockArray[m_ID][i] % 8;
		m_block[i].y = BlockArray[m_ID][i] / 8;
	}
}

void TetrisShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		m_sprite.setPosition((m_block[i].x * 18) + (m_position.x * 18), (m_block[i].y * 18) + (m_position.y * 18));
		target.draw(m_sprite);
	}
}
