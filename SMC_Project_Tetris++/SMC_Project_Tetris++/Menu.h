#pragma once

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_ELEMENTS 3

class Menu
{
public:
	Menu(unsigned int witdh, unsigned int height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void ModeGame();
	void Select();

private:
	sf::RenderWindow m_window;
	int m_selectedItemIndex;
	int m_selectedModeGame;
	sf::Font m_fontMenu;
	sf::Text m_menu[MAX_NUMBER_ELEMENTS];
	sf::Text m_modeGame[2];
	sf::Texture m_textureMenu;
	sf::Sprite m_spriteMenu;
	bool m_menuOrGame;
	uint16_t m_levelSound;
};
