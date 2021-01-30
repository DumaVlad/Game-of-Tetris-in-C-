#include <iostream>
#include "Menu.h"
#include "Game.h"
#include "Game_2P.h"
#include "Options.h"
#include "Highscore.h"

Menu::Menu(unsigned int width, unsigned int height)
	: m_window{ sf::VideoMode{width,height}, "Menu" }, m_selectedItemIndex{ 0 }, m_selectedModeGame{ 0 }, m_fontMenu{}, m_menu{}, m_modeGame{}, m_textureMenu{}, m_spriteMenu{}, m_menuOrGame{ 1 }, m_highscoreOrGame{ false }, m_levelSound{ 2 }
{
	if (!m_fontMenu.loadFromFile("../Resources/Fonts/arial.ttf"))
	{
		std::cout << "Could not load font in Menu class !! \n";
	}


	InitializeMenu(width, height);
	InitializeModeGame(width, height);


	if (!m_textureMenu.loadFromFile("../Resources/Images/tetris600x600.jpg"))
	{
		std::cout << "Can't load the texture from the file in Menu class !!\n";
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
	{
		m_modeGame[0].setFillColor(sf::Color::Red);
		m_modeGame[1].setFillColor(sf::Color::White);
		for (uint16_t i = 0; i < MAX_NUMBER_ELEMENTS; i++)
		{
			window.draw(m_menu[i]);
		}
	}
	else
		for (uint8_t i = 0;i < 2;i++)
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
		if (m_selectedModeGame + 1 < MAX_NUMBER_ELEMENTS)
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
		return m_selectedModeGame + 2;
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
							m_highscoreOrGame = false;
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
							std::cout << "\nHighscore button has been pressed!" << std::endl;
							ModeGame();
							m_highscoreOrGame = true;
						}
						break;
						case 3:
						{
							std::cout << "\nYou closed the game! \nGOOD BYE!! See You soon!" << std::endl;
							m_window.close();
						}
						break;
						case 4:
						{
							std::cout << "\nSingleplayer button has been pressed!" << std::endl;
							if (!m_highscoreOrGame)
							{
								m_menuOrGame = false;
								Game game;
								game.Run(m_menuOrGame, m_levelSound);
								m_selectedModeGame = 0;
							}
							else
							{
								Highscore highscore(0);
								highscore.runHighscore();
							}
						}
						break;
						case 5:
						{
							std::cout << "\nMultiplayer button has been pressed!" << std::endl;
							if (!m_highscoreOrGame)
							{
								m_menuOrGame = false;
								Game_2P game;
								game.Run(m_menuOrGame, m_levelSound);
								m_selectedModeGame = 0;
							}
							else
							{
								Highscore highscore(1);
								highscore.runHighscore();
							}
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

void Menu::InitializeMenu(unsigned int width, unsigned int height)
{
	for (uint8_t i = 0; i < MAX_NUMBER_ELEMENTS; i++)
	{
		m_menu[i].setFont(m_fontMenu);
		m_menu[i].setFillColor(sf::Color::White);
		m_menu[i].setOutlineColor(sf::Color::Black);
		m_menu[i].setOutlineThickness(3);
		m_menu[i].setCharacterSize(35);
		m_menu[i].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_ELEMENTS + 1) * (i + 1)));
	}

	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setString("Play");
	m_menu[1].setString("Options");
	m_menu[2].setString("Highscore");
	m_menu[3].setString("Exit");

}

void Menu::InitializeModeGame(unsigned int width, unsigned int height)
{
	for (uint8_t i = 0; i < 2; i++)
	{
		m_modeGame[i].setFont(m_fontMenu);
		m_modeGame[i].setOutlineColor(sf::Color::Black);
		m_modeGame[i].setOutlineThickness(5);
		m_modeGame[i].setCharacterSize(50);
	}

	m_modeGame[0].setString("Singleplayer");
	m_modeGame[1].setString("Multiplayer");
	m_modeGame[0].setPosition(sf::Vector2f(width / 3.8, height / 8 * 1.5));
	m_modeGame[1].setPosition(sf::Vector2f(width / 3.7, height / 4 * 2.5));

}
