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

class Board : public IBoard
{
public:
	using Position = sf::Vector2i;

public:
	Board(Position, IGame&);
	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;

private:
	void MarkLinesForRemoval();

private:
};