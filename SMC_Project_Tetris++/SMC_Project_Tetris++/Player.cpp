#include "Player.h"

Player::Player(const std::string& playerName, const uint16_t width, const uint16_t height)
	: m_playerName{ playerName }, m_font{}, m_levelText{}, m_scoreText{}, m_clearedLinesText{}, m_playerNameText{}, m_score{ 0 }, m_loadSoftScore{ 0 }, m_linesCleared{ 0 }
{
	m_font.loadFromFile("../Resources/Fonts/arial.ttf");
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(20);

	m_levelText.setFont(m_font);
	m_levelText.setCharacterSize(20);
	m_playerNameText.setFont(m_font);
	m_playerNameText.setCharacterSize(20);
	m_playerNameText.setPosition(sf::Vector2f{ (float)width * 18 + 10 , 100.f });
	m_scoreText.setPosition(sf::Vector2f{ (float)width * 18 + 10, 200.f });
	m_levelText.setPosition(sf::Vector2f{ (float)width * 18 + 10, 300.f });

	m_clearedLinesText.setFont(m_font);
	m_clearedLinesText.setCharacterSize(20);
	m_clearedLinesText.setPosition((float)width * 18 + 10, 400.f);
}

std::string Player::GetPlayerName()
{
	return m_playerName;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_playerNameText);
	window.draw(m_levelText);
	window.draw(m_scoreText);
	window.draw(m_clearedLinesText);
}

void Player::Reset()
{
	m_linesCleared = 0;
	m_score = 0;
}

void Player::AddPressedScore(uint32_t score)
{
	m_loadSoftScore += score;
}

void Player::SumPressedScore()
{
	m_score += m_loadSoftScore;
	m_loadSoftScore = 0;
}

void Player::AddClearedLines(uint16_t num)
{
	m_linesCleared += num;
	int level = m_linesCleared / 10;

	switch (num)
	{
	case(1):
	{
		m_score += 40 * (level + 1);
		break;
	}
	case (2):
	{
		m_score += 100 * (level + 1);
		break;
	}
	case (3):
	{
		m_score += 300 * (level + 1);
		break;
	}
	case (4):
	{
		m_score += 1200 * (level + 1);
		break;
	}
	default:
		break;
	}
}

void Player::Update(const sf::Time& dt)
{
	m_playerNameText.setString(std::string("Good Luck, \n" + m_playerName));
	m_levelText.setString(std::string("Level:\n" + std::to_string(m_linesCleared / 10)));
	m_scoreText.setString(std::string("Score:\n" + std::to_string(m_score)));
	m_clearedLinesText.setString(std::string("Lines:\n" + std::to_string(m_linesCleared)));
}

int Player::GetLevel() const
{
	return m_linesCleared / 10;
}

uint32_t Player::GetScore() const
{
	return m_score;
}
