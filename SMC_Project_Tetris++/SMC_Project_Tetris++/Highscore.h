#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

#define MAX_NUMBER_PLAYERS 10

class Highscore
{
public:
	Highscore();
	void draw();
	void runHighscore();
	~Highscore() = default;

private:
	void InitializeScorePlayerList();

private:
	sf::RenderWindow m_renderWindowHighscore;
	sf::Texture m_textureHighscore;
	sf::Font m_fontHighscore;
	sf::Sprite m_spriteHighscore;
	sf::Text m_playersList[MAX_NUMBER_PLAYERS];
	void FileReader();
	static bool m_comparePlayers(const std::pair<std::string, std::string>& Player1, const std::pair<std::string, std::string>& Player2) {
		return (std::stoi(Player1.second) > std::stoi(Player2.second));
	}
};
