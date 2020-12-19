#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "Options.h"

Menu::Menu(unsigned int witdh, unsigned int height)
	: m_window{ sf::VideoMode{witdh,height}, "Menu" }, m_selectedItemIndex{ 0 }, m_selectedModeGame{ 0 }, m_fontMenu{}, m_menu{}, m_modeGame{}, m_textureMenu{}, m_spriteMenu{}, m_menuOrGame{ 1 }, m_levelSound{ 2 }
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
	m_menu[0].setPosition(sf::Vector2f(witdh / 2.2, height / (MAX_NUMBER_ELEMENTS + 1) * 1));

	m_menu[1].setFont(m_fontMenu);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setOutlineColor(sf::Color::Black);
	m_menu[1].setOutlineThickness(3);
	m_menu[1].setString("Options");
	m_menu[1].setPosition(sf::Vector2f(witdh / 2.2, height / (MAX_NUMBER_ELEMENTS + 1) * 2));

	m_menu[2].setFont(m_fontMenu);
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setOutlineColor(sf::Color::Black);
	m_menu[2].setOutlineThickness(3);
	m_menu[2].setString("Exit");
	m_menu[2].setPosition(sf::Vector2f(witdh / 2.2, height / (MAX_NUMBER_ELEMENTS + 1) * 3));

	m_modeGame[0].setFont(m_fontMenu);
	m_modeGame[0].setFillColor(sf::Color::Red);
	m_modeGame[0].setOutlineColor(sf::Color::Black);
	m_modeGame[0].setOutlineThickness(5);
	m_modeGame[0].setString("Singleplayer");
	m_modeGame[0].setCharacterSize(50);
	m_modeGame[0].setPosition(sf::Vector2f(witdh / 3.8, height / 8 * 1.5));

	m_modeGame[1].setFont(m_fontMenu);
	m_modeGame[1].setFillColor(sf::Color::White);
	m_modeGame[1].setOutlineColor(sf::Color::Black);
	m_modeGame[1].setOutlineThickness(5);
	m_modeGame[1].setString("Multiplayer");
	m_modeGame[1].setCharacterSize(50);
	m_modeGame[1].setPosition(sf::Vector2f(witdh / 3.7, height / 4 * 2.5));


	if (!m_textureMenu.loadFromFile("tetris600x600.jpg"))
	{
		std::cout << "Can't load the texture from the file !" << std::endl;
	}

	m_textureMenu.setSmooth(true);
	m_spriteMenu.setTexture(m_textureMenu);
	m_spriteMenu.setOrigin(0, 0);

	Select();
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	if (!m_selectedModeGame)
		for (int i = 0; i < MAX_NUMBER_ELEMENTS; i++)
		{
			window.draw(m_menu[i]);
		}
	else
		for (int i = 0;i < 2;i++)
		{
			window.draw(m_modeGame[i]);
		}
}

void Menu::MoveUp()
{
	if (!m_selectedModeGame)
	{
		if (m_selectedItemIndex - 1 >= 0)
		{
			m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
			m_selectedItemIndex--;
			m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	else
		if (m_selectedModeGame > 2)
		{
			m_modeGame[m_selectedModeGame - 2].setFillColor(sf::Color::White);
			m_selectedModeGame--;
			m_modeGame[m_selectedModeGame - 2].setFillColor(sf::Color::Red);
		}
}

void Menu::MoveDown()
{
	if (!m_selectedModeGame)
	{
		if (m_selectedItemIndex + 1 < MAX_NUMBER_ELEMENTS)
		{
			m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
			m_selectedItemIndex++;
			m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
		}
	}
	else
		if (m_selectedModeGame < 3)
		{
			m_modeGame[m_selectedModeGame - 2].setFillColor(sf::Color::White);
			m_selectedModeGame++;
			m_modeGame[m_selectedModeGame - 2].setFillColor(sf::Color::Red);
		}
}


int Menu::GetPressedItem()
{
	if (!m_selectedModeGame)
		return m_selectedItemIndex;
	else
		return m_selectedModeGame + 1;
}

void Menu::ModeGame()
{
	m_selectedModeGame = 2;
	m_window.clear();
	m_window.draw(m_spriteMenu);
	draw(m_window);
	m_window.display();
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

					case sf::Keyboard::Escape:
						m_selectedModeGame = 0;
						break;

					case sf::Keyboard::Return:
						switch (GetPressedItem())
						{
						case 0:
						{
							std::cout << "\nPlay button has been pressed!" << std::endl;
							ModeGame();
						}
						break;
						case 1:
						{
							std::cout << "\nOptions button has been pressed!" << std::endl;
							Options options;
							options.RunOptions(m_levelSound);
						}
						break;
						case 2:
						{
							std::cout << "\nYou closed the game! \nGOOD BYE!! See You soon!" << std::endl;
							m_window.close();
						}
						break;
						case 3:
						{
							std::cout << "\nSingleplayer button has been pressed!" << std::endl;
							m_menuOrGame = 0;
							Game game;
							game.Run(m_menuOrGame, m_levelSound);
							m_selectedModeGame = 0;
						}
						break;
						case 4:
						{
							std::cout << "\nMultiplayer button has been pressed!" << std::endl;
							std::cout << "Still in Work!!" << std::endl;
						}
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
			m_window.clear();
			m_window.draw(m_spriteMenu);
			draw(m_window);
			m_window.display();
		}
	}
}