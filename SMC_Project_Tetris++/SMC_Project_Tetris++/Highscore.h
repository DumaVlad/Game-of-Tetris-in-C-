#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

#define MAX_NUMBER_PLAYERS 10
typedef std::pair<std::string, std::string> typePlayer;

class Highscore
{
public:
	Highscore();
	void draw();
	void runHighscore();
	~Highscore() = default;

private:
	void InitializeScorePlayerList();
	void FileReader();

private:
	sf::RenderWindow m_renderWindowHighscore;
	sf::Texture m_textureHighscore;
	sf::Font m_fontHighscore;
	sf::Sprite m_spriteHighscore;
	sf::Text m_playersList[MAX_NUMBER_PLAYERS];
	static bool m_comparePlayers(const typePlayer& Player1, const typePlayer& Player2) {
		return std::stoi(Player1.second) > std::stoi(Player2.second);
	}
	sf::Text m_textModeGame;
	uint16_t m_modeGame;
};
