#include "Board.h"
#include <iostream>
#include <algorithm>

FieldInfo::FieldInfo(sf::Texture& texture, uint16_t id)
{
	sf::IntRect rectangle{ (id % 7) * 18, 0, 18, 18 };
	m_Sprite.setTexture(texture);
	m_Sprite.setTextureRect(rectangle);
}

Field& Field::operator=(const Field& field)
{
	this->m_Occupied = field.m_Occupied;
	this->m_Visible = field.m_Visible;
	this->m_Info = field.m_Info;

	return *this;
}

Board::Board(Position size, Game& game)
	: m_Game{ game }, m_Fields{}, m_FieldInfos{}, m_Size{ size }, m_ToBeCleaned{}, m_ElapsedTime{ 0.f }, m_ToRemoveBlocks{ false }
{
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
			m_Fields[Convert2DTo1D(x, y)] = std::make_unique<Field>();

	for (int id = 0; id < 7; id++)
		m_FieldInfos[id] = std::make_unique<FieldInfo>(m_Game.m_Texture, id);
}

void Board::Update(const sf::Time& dt)
{
	MarkLinesForRemoval();
	if (m_ToRemoveBlocks)
	{
		m_ElapsedTime += dt.asSeconds();
		Blink();
		if (m_ElapsedTime > 0.6f)
		{
			m_ElapsedTime = 0.f;
			CleanLines();
		}
	}
}

void Board::Clean()
{
	for (uint16_t x = 0; x < m_Size.x; x++)
	{
		for (uint16_t y = 0; y < m_Size.y; y++)
		{
			auto field = GetField(x, y);
			field->m_Occupied = false;
			field->m_Visible = true;
			field->m_Info = nullptr;
		}
	}
}

void Board::AddBlock(uint16_t id, std::array<Position, 16> block)
{
}

bool Board::IsOccupied(std::array<Position, 16> block)
{
	return false;
}

void Board::Draw(sf::RenderWindow& window)
{
}

Field* Board::GetField(uint16_t x, uint16_t y)
{
	return nullptr;
}

int Board::Convert2DTo1D(uint16_t x, uint16_t y)
{
	return 0;
}

void Board::CleanLines()
{
}

void Board::MarkLinesForRemoval()
{
}

void Board::Blink()
{
}
