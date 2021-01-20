#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <unordered_map>
#include "IGame.h"
#include "IBoard.h"

class IGame; // for using methods from class Game

class Board_2P : public IBoard
{
public:
	using Position = sf::Vector2i;

public:
	Board_2P(Position, IGame&);
	Board_2P(const Board_2P& other) = delete;
	Board_2P& operator=(const Board_2P& other) = delete;
	void GenerateDarkHole(uint16_t, Position);
	void DestroyDarkHole(Position);

private:
	void MarkLinesForRemoval();

private:
};