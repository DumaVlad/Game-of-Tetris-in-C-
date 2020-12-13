#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

#define MAX_NUMBER_CONTROLS 8

class Options
{
public:
	Options();
	void draw();
	void RunOptions();
	~Options();

private:
	sf::RenderWindow m_renderWindowOptions;
	sf::Texture m_textureOptions;
	sf::Font m_fontOptions;
	sf::Sprite m_spriteOptions;
	sf::Text m_controlsGame[MAX_NUMBER_CONTROLS];
};

