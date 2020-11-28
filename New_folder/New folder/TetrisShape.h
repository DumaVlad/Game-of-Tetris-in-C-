#pragma once
#include "Shape.h"
#include "Directions.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <array>

class TetrisShape : public sf::Drawable
{

public:
	using Position = sf::Vector2i;

public:
	TetrisShape(sf::Texture& texture, uint16_t id);
	~TetrisShape() = default;

	void Rotate();
	void Move(Direction direction);
	void SetPosition(const Position& position);
	void RevertState();
	void ScaleUp();
	void ScaleDown();
	std::array<Position, 9> GetBlockPosition() const;
	std::array<Position, 9> GetFutureBlockPosition(Direction direction) const;
	uint16_t GetID() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	Position m_Position;
	uint16_t m_CurrentRotation;
	uint16_t m_ID;
	std::array<Position, 9> m_Block;
	std::array<Position, 9> m_OldBlock;
	mutable sf::Sprite m_Sprite;
};

