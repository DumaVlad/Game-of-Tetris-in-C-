#include "IGame.h"
#include "IGame.h"
#include <iostream>

IGame::IGame(const unsigned int width, const unsigned int height)
	: m_renderWindow{ sf::VideoMode {width * 18 + 120, height * 18}, "TETRIS++", sf::Style::Default }, m_texture{}, m_separationLine{}, m_tetrisShape{ nullptr }, m_preview{ nullptr }, m_board{}, 
	m_score{ width, height }, m_elapsedTime{ sf::Time::Zero }, m_ID{ Utils::GetRandomNumber(7) }, m_gameplayMusic{}, m_pause{false}, m_pauseMenu{}, m_fontOptions{}, m_textPauseMenu{}
{
	m_separationLine.setSize(sf::Vector2f{ 2.f, height * 18.f });
	m_separationLine.setPosition(sf::Vector2f{ width * 18.f, 0 });
	m_separationLine.setFillColor(sf::Color::Red);

	m_pauseMenu.setSize(sf::Vector2f{ 250.f,150.f });
	m_pauseMenu.setFillColor(sf::Color(0, 250, 154));
	m_pauseMenu.setOutlineColor(sf::Color::White);
	m_pauseMenu.setOutlineThickness(4);
	m_pauseMenu.setPosition(sf::Vector2f{(width * 18.f + 150.f) / 4.5f,(height * 18.f) / 3.f });

	if (!m_fontOptions.loadFromFile("../Resources/Fonts/arial.ttf"))
		std::cout << "Could not load font in Game Interface !! \n";
	if (!m_texture.loadFromFile("../Resources/Images/Blocks.png"))
		std::cout << "Could not load texture in Game Interface !! \n";
	if (!m_gameplayMusic.openFromFile("../Resources/Sounds/Tetris.wav"))
		std::cout << "Could not load music in Game Interface !! \n";

	m_textPauseMenu[0].setFont(m_fontOptions);
	m_textPauseMenu[0].setFillColor(sf::Color(0, 191, 255));
	m_textPauseMenu[0].setOutlineColor(sf::Color::Black);
	m_textPauseMenu[0].setOutlineThickness(3);
	m_textPauseMenu[0].setCharacterSize(25);
	m_textPauseMenu[0].setString("Pause Menu");
	m_textPauseMenu[0].setPosition(sf::Vector2f((width * 18.f + 150.f) / 3.1f, (height * 18.f) / 3.f));

	for (int i = 1; i < 4; i++)
	{
		m_textPauseMenu[i].setFont(m_fontOptions);
		m_textPauseMenu[i].setFillColor(sf::Color::White);
		m_textPauseMenu[i].setOutlineColor(sf::Color::Black);
		m_textPauseMenu[i].setOutlineThickness(3);
		m_textPauseMenu[i].setCharacterSize(15);
		m_textPauseMenu[i].setPosition(sf::Vector2f((width * 18.f + 150.f) / 3.3f, (height * 18.f) / 3.f + 40.f * i));
	}
	m_textPauseMenu[1].setString("Press Enter for Continue");
	m_textPauseMenu[2].setString("Press O for Options");
	m_textPauseMenu[3].setString("Press Escape for Exit");
}