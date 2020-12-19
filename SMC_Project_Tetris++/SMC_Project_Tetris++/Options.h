#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

#define MAX_NUMBER_CONTROLS 9

class Options
{
public:
	Options();
	void draw(uint16_t& levelSound);
	void RunOptions(uint16_t& levelSound);
	~Options();

private:
	sf::RenderWindow m_renderWindowOptions;
	sf::Texture m_textureOptions;
	sf::Font m_fontOptions;
	sf::Sprite m_spriteOptions;
	sf::Text m_controlsGame[MAX_NUMBER_CONTROLS];
	sf::Text m_controlSound[6];
};

