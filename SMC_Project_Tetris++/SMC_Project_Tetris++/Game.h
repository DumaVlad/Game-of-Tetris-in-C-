#pragma once
#include "TetrisShape.h"
#include "Board.h"
#include "Score.h"
#include "Config.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>

class Game
{
	friend class Board;

public:
	using Position = sf::Vector2i;

public:
	Game();
	void Run(bool& menuOrGame, uint16_t& levelSound);

private:
	void Proceed(Direction);
	void Update(const sf::Time&);
	void Rotate();
	void ScaleUp();
	void ScaleDown();
	void CreateShape();
	bool IsValidMovement(std::array<Position, 16>);
	bool IsOccupied(int, int);
	void ProcessEvents(bool& menuOrGame, uint16_t& levelSound);
	void Render();

private:
	sf::RenderWindow m_RenderWindow;
	sf::Texture m_Texture;
	sf::RectangleShape m_SeparationLine;
	std::unique_ptr<TetrisShape> m_TetrisShape;
	std::unique_ptr<TetrisShape> m_Preview;
	std::unique_ptr<Board> m_Board;
	sf::Time m_ElapsedTime;
	sf::Music m_GameplayMusic;
	Score m_Score;
	int m_ID;
	bool m_pause;
};

