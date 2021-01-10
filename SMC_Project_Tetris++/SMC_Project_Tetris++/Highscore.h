#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

#define MAX_NUMBER_NAMES 10

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
	sf::Text m_scorePlayersList[MAX_NUMBER_NAMES];
	void FileReader();
};
