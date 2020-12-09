#include "Menu.h"
#include "Game.h"
#include <iostream>

Menu::Menu()
	: m_window{ sf::VideoMode{600,600}, "Menu", sf::Style::Default }, m_selectedItemIndex{ 0 }, m_menu{}, m_menuOrGame{ 1 }, m_textureMenu{}, m_textureShape{}, m_spriteMenu{}
{
	if (!m_fontMenu.loadFromFile("arial.ttf"))
	{
		//handle error
	}
	sf::Vector2u size = m_window.getSize();
	m_menu[0].setFont(m_fontMenu);
	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setOutlineColor(sf::Color::Black);
	m_menu[0].setOutlineThickness(3);
	m_menu[0].setString("Play");
	m_menu[0].setPosition(sf::Vector2f(size.x / 2.2, size.y / (MAX_NUMBER_ELEMENTS + 1) * 1));

	m_menu[1].setFont(m_fontMenu);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setOutlineColor(sf::Color::Black);
	m_menu[1].setOutlineThickness(3);
	m_menu[1].setString("Options");
	m_menu[1].setPosition(sf::Vector2f(size.x / 2.2, size.y / (MAX_NUMBER_ELEMENTS + 1) * 2));

	m_menu[2].setFont(m_fontMenu);
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setOutlineColor(sf::Color::Black);
	m_menu[2].setOutlineThickness(3);
	m_menu[2].setString("Exit");
	m_menu[2].setPosition(sf::Vector2f(size.x / 2.2, size.y / (MAX_NUMBER_ELEMENTS + 1) * 3));

	if (!m_textureMenu.loadFromFile("tetris600x600.jpg"))
	{
		std::cout << "Can't load the texture from the file !" << std::endl;
	}

	m_textureMenu.setSmooth(true);
	m_spriteMenu.setTexture(m_textureMenu);
	m_spriteMenu.setOrigin(0, 0);

	m_window.draw(m_spriteMenu);
	draw(m_window);
	m_window.display();
	Select();
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_ELEMENTS; i++)
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

void Menu::Select()
{
	while (m_window.isOpen())
	{
		if (m_menuOrGame)
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				switch (event.type)
				{
				case::sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						MoveUp();
						break;

					case sf::Keyboard::Down:
						MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (GetPressedItem())
						{
						case 0:
						{
							std::cout << "Play button has been pressed!" << std::endl;
							m_menuOrGame = 0;
							Game game;
							game.Run();
						}
						break;
						case 1:
							std::cout << "Options button has been pressed!" << std::endl;
							break;
						case 2:
							m_window.close();
							break;
						}
						break;
					}
					break;
				case sf::Event::Closed:
					m_window.close();
					break;
				}
			}
		}
	}
}