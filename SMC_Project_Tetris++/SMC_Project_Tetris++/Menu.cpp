#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!m_fontMenu.loadFromFile("arial.ttf"))
	{
		//handle error
	}

	m_menu[0].setFont(m_fontMenu);
	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setOutlineColor(sf::Color::Black);
	m_menu[0].setOutlineThickness(3);
	m_menu[0].setString("Play");
	m_menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ELEMENTS + 1) * 1));

	m_menu[1].setFont(m_fontMenu);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setOutlineColor(sf::Color::Black);
	m_menu[1].setOutlineThickness(3);
	m_menu[1].setString("Options");
	m_menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ELEMENTS + 1) * 2));

	m_menu[2].setFont(m_fontMenu);
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setOutlineColor(sf::Color::Black);
	m_menu[2].setOutlineThickness(3);
	m_menu[2].setString("Exit");
	m_menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ELEMENTS + 1) * 3));

	m_selectedItemIndex = 0;

}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0;i < MAX_NUMBER_ELEMENTS;i++)
	{
		window.draw(m_menu[i]);
	}
}

void Menu::MoveUp()
{
	if (m_selectedItemIndex - 1 >= 0)
	{
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
		m_selectedItemIndex--;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (m_selectedItemIndex + 1 < MAX_NUMBER_ELEMENTS)
	{
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
		m_selectedItemIndex++;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem()
{
	return m_selectedItemIndex;
}
