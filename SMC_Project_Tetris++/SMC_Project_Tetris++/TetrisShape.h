#pragma once
#include "Shapes.h"
#include "Directions.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <array>
#include "Utils.h"

class TetrisShape : public sf::Drawable
{
public:
	using Position = sf::Vector2i;

public:
	TetrisShape(sf::Texture&, uint16_t, Position);
	~TetrisShape() = default;

	uint16_t GetID() const;
	std::array<Position, BLOCK_ARRAY_COLUMNS> GetBlockPosition() const;
	std::array<Position, BLOCK_ARRAY_COLUMNS> GetFutureBlockPosition(Direction) const;
	void Read();
	void SetPosition(const Position&);
	void Rotate();
	void Move(Direction);
	void ScaleUp();
	void ScaleDown();

public:
	std::array<Position, BLOCK_ARRAY_COLUMNS> m_block;

private:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	
private:
	Position m_position;
	uint16_t m_currentRotation;
	uint16_t m_ID;
	mutable sf::Sprite m_sprite;
};

