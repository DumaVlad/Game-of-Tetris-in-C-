#pragma once
#include<cstdint>
#include<string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Utils.h"

class Player
{
public:

	Player(const std::string& playerName, const uint16_t width, const uint16_t height);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;

public:
	std::string GetPlayerName();
	void Draw(sf::RenderWindow& window);
	void Reset();
	void AddPressedScore(uint32_t score);
	void SumPressedScore();
	void AddClearedLines(uint16_t num);
	void Update(const sf::Time& dt);
	int GetLevel() const;
	uint32_t GetScore() const;

private:
	std::string m_playerName;
	sf::Font m_font;
	sf::Text m_levelText;
	sf::Text m_scoreText;
	sf::Text m_clearedLinesText;
	sf::Text m_playerNameText;
	uint32_t m_score;
	uint32_t m_loadSoftScore;
	uint32_t m_linesCleared;
};


