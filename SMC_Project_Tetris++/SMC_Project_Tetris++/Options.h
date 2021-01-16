#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

#define MAX_NUMBER_CONTROLS 10
#define MAX_NUMBER_CONTROLS_MP 18

class Options
{
public:
	Options();
	void draw(uint16_t& levelSound);
	void RunOptions(uint16_t& levelSound);
	~Options();
private:
	void InitializeControlsSingleplayerGame();
	void InitializeControlsMultiplayerGame();
	void InitializeControlSound();
	void InitializeTextPage();

private:
	sf::RenderWindow m_renderWindowOptions;
	sf::Texture m_textureOptions;
	sf::Font m_fontOptions;
	sf::Sprite m_spriteOptions;
	sf::Text m_controlsSingleplayerGame[MAX_NUMBER_CONTROLS];
	sf::Text m_controlsMultiplayerGame[MAX_NUMBER_CONTROLS_MP];
	uint16_t m_page;
	sf::Text m_textPage[2];
	sf::Text m_controlSound[6];
};

