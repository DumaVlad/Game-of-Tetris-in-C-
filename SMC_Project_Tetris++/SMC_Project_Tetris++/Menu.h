#pragma once

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_ELEMENTS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

private:
	int m_selectedItemIndex;
	sf::Font m_fontMenu;
	sf::Text m_menu[MAX_NUMBER_ELEMENTS];
};

