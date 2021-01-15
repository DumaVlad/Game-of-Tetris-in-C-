#include "IGame.h"
#include "IGame.h"
#include <iostream>

IGame::IGame(const unsigned int width, const unsigned int height)
	: m_renderWindow{ sf::VideoMode {width * 18 + 180, height * 18}, "TETRIS++", sf::Style::Default }, m_texture{}, m_separationLine{}, m_tetrisShape{ nullptr }, m_preview{ nullptr }, m_board{},
	m_elapsedTime{ sf::Time::Zero }, m_ID{ Utils::GetRandomNumber(7) }, m_gameplayMusic{}, m_pause{ 3 }, m_pauseMenu{}, m_fontOptions{}, m_textPauseMenu{}, m_player{ nullptr }
{
	m_separationLine.setSize(sf::Vector2f{ 2.f, height * 18.f });
	m_separationLine.setPosition(sf::Vector2f{ width * 18.f, 0 });
	m_separationLine.setFillColor(sf::Color::Red);

	m_pauseMenu.setFillColor(sf::Color(0, 250, 154));
	m_pauseMenu.setOutlineColor(sf::Color::White);
	m_pauseMenu.setOutlineThickness(4);
	m_pauseMenu.setPosition(sf::Vector2f{ (width * 18.f + 150.f) / 4.5f,(height * 18.f) / 3.f });

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

	for (uint16_t i = 1; i < 4; i++)
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

	m_textGameOverMenu[0].setFont(m_fontOptions);
	m_textGameOverMenu[0].setFillColor(sf::Color::Red);
	m_textGameOverMenu[0].setOutlineColor(sf::Color::Black);
	m_textGameOverMenu[0].setOutlineThickness(3);
	m_textGameOverMenu[0].setCharacterSize(25);
	m_textGameOverMenu[0].setString("GAME OVER");
	m_textGameOverMenu[0].setPosition(sf::Vector2f((width * 18.f + 150.f) / 3.1f, (height * 18.f) / 3.f));

	for (uint16_t i = 1;i < 5;i++)
	{
		m_textGameOverMenu[i].setFont(m_fontOptions);
		m_textGameOverMenu[i].setFillColor(sf::Color::White);
		m_textGameOverMenu[i].setOutlineColor(sf::Color::Black);
		m_textGameOverMenu[i].setOutlineThickness(3);
		m_textGameOverMenu[i].setCharacterSize(15);
		m_textGameOverMenu[i].setPosition(sf::Vector2f((width * 18.f + 150.f) / 3.3f, (height * 18.f) / 3.f + 40.f * i));
	}
	m_textGameOverMenu[1].setString("Press Enter for Continue");
	m_textGameOverMenu[2].setString("Press O for Options");
	m_textGameOverMenu[3].setString("Press H for Highscore");
	m_textGameOverMenu[4].setString("Press Escape for Exit");

	m_playerNameBox.setFont(m_fontOptions);
	m_playerNameBox.setFillColor(sf::Color::Red);
	m_playerNameBox.setOutlineColor(sf::Color::Black);
	m_playerNameBox.setOutlineThickness(3);
	m_playerNameBox.setCharacterSize(30);
	m_playerNameBox.setString("Insert your name:");
	m_playerNameBox.setPosition(sf::Vector2f((width * 18.f + 25.f) / 3.1f, (height * 18.f) / 3.f));

	m_playerNameText.setFont(m_fontOptions);
	m_playerNameText.setFillColor(sf::Color::White);
	m_playerNameText.setOutlineColor(sf::Color::Black);
	m_playerNameText.setOutlineThickness(3);
	m_playerNameText.setCharacterSize(25);
	m_playerNameText.setPosition(sf::Vector2f((width * 18.f + 70.f) / 3.1f, (height * 18.f) / 3.f + 70.f));

}

void IGame::Proceed(Direction direction)
{
	if (!m_tetrisShape)
		return;

	if (IsValidMovement(m_tetrisShape->GetFutureBlockPosition(direction)))
	{
		m_tetrisShape->Move(direction);
		if (direction == Direction::UserPressedDown)
			m_player->AddPressedScore(1);
	}
	else
	{
		if (direction == Direction::Down || direction == Direction::UserPressedDown)
		{
			int id = m_tetrisShape->GetID();
			m_board->AddBlock(id, m_tetrisShape->GetBlockPosition());
			m_tetrisShape.reset(nullptr);
			m_player->SumPressedScore();
		}
	}
}

void IGame::Rotate()
{
	if (!m_tetrisShape)
		return;

	TetrisShape temp = *m_tetrisShape;
	temp.Rotate();
	if (!IsValidMovement(temp.GetBlockPosition()))
		return;
	else
		m_tetrisShape->Rotate();
}

void IGame::ScaleUp()
{
	if (!m_tetrisShape)
		return;

	TetrisShape temp = *m_tetrisShape;
	temp.ScaleUp();
	if (!IsValidMovement(temp.GetBlockPosition()))
		return;
	else
		m_tetrisShape->ScaleUp();
}

void IGame::ScaleDown()
{
	if (!m_tetrisShape)
		return;

	TetrisShape temp = *m_tetrisShape;
	temp.ScaleDown();
	if (!IsValidMovement(temp.GetBlockPosition()))
		return;
	else
		m_tetrisShape->ScaleDown();
}

bool IGame::IsOccupied(uint16_t x, uint16_t y)
{
	return m_board->GetField(x, y)->m_Occupied;
}

std::pair<uint16_t, uint16_t> IGame::GetFreePosition(uint16_t x, uint16_t y)
{
	for (--y; y >= 0; y--)
	{
		if (!IsOccupied(x, y))
		{
			std::pair<uint16_t, uint16_t> field(x, y);
			return field;
		}
	}
}
