#pragma once
#include "Shapes.h"
#include "Directions.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <array>

class TetrisShape : public sf::Drawable
{
public:
	using Position = sf::Vector2i;

public:
	TetrisShape(sf::Texture&, uint16_t, Position);
	~TetrisShape() = default;

	uint16_t GetID() const;
	std::array<Position, 16> GetBlockPosition() const;
	std::array<Position, 16> GetFutureBlockPosition(Direction) const;
	void SetPosition(const Position&);
	void Rotate();
	void Move(Direction);
	void ScaleUp();
	void ScaleDown();

private:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
	Position m_Position;
	uint16_t m_CurrentRotation;
	uint16_t m_ID;
	std::array<Position, 16> m_Block;
	mutable sf::Sprite m_Sprite;
};

