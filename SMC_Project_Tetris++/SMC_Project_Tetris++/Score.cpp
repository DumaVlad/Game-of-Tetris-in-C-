#include "Score.h"

Score::Score()
	:m_Font{}, m_LevelText{}, m_ScoreText{}, m_ClearedLinesText{}, m_Score{0}, m_LoadPressedScore{0}, m_LinesCleared{0}
{
	m_Font.loadFromFile("arial.ttf");
	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(20);

	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(20);
	m_ScoreText.setPosition(sf::Vector2f{ BOARD_WIDTH * 18 + 20, 200.f });
	m_LevelText.setPosition(sf::Vector2f{ BOARD_WIDTH * 18 + 20, 300.f });

	m_ClearedLinesText.setFont(m_Font);
	m_ClearedLinesText.setCharacterSize(20);
	m_ClearedLinesText.setPosition(sf::Vector2f{ BOARD_WIDTH * 18 + 20, 400.f });
}

void Score::Draw(sf::RenderWindow& window)
{
	window.draw(m_LevelText);
	window.draw(m_ScoreText);
	window.draw(m_ClearedLinesText);
}

void Score::Reset()
{
	m_LinesCleared = 0;
	m_Score = 0;
}

void Score::AddPressedScore(int score)
{
	m_LoadPressedScore += score;
}

void Score::SumPressedScore()
{
	m_Score += m_LoadPressedScore;
	m_LoadPressedScore = 0;
}

void Score::AddClearedLines(int number)
{
	m_LinesCleared += number;
	int level = m_LinesCleared / 10;

	switch (number)
	{
	case(1):
	{
		m_Score += 40 * (level + 1);
		break;
	}
	case (2):
	{
		m_Score += 100 * (level + 1);
		break;
	}
	case (3):
	{
		m_Score += 300 * (level + 1);
		break;
	}
	case (4):
	{
		m_Score += 1200 * (level + 1);
		break;
	}
	default:
		break;
	}
}

void Score::Update(const sf::Time& dt)
{
	m_LevelText.setString(std::string("Level:\n" + std::to_string(m_LinesCleared / 10)));
	m_ScoreText.setString(std::string("Score:\n" + std::to_string(m_Score)));
	m_ClearedLinesText.setString(std::string("Lines cleared:\n" + std::to_string(m_LinesCleared)));
}

int Score::GetLevel() const
{
	return m_LinesCleared / 10;
}

int Score::GetScore() const
{
	return m_Score;
}
