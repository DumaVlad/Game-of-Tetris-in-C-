#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Config.h"

class Score
{
public:
	Score();
	Score(const Score& score) = delete;
	Score& operator=(const Score& score) = delete;

	void Draw(sf::RenderWindow& window);
	void Reset();
	void AddPressedScore(int score);
	void SumPressedScore();
	void AddClearedLines(int number);
	void Update(const sf::Time& dt);
	int GetLevel() const;
	int GetScore() const;

private:
	sf::Font m_Font;
	sf::Text m_LevelText;
	sf::Text m_ScoreText;
	sf::Text m_ClearedLinesText;
	int m_Score;
	int m_LoadPressedScore;
	int m_LinesCleared;
};

