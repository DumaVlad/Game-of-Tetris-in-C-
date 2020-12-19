#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Options.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game()
	: m_RenderWindow{ sf::VideoMode{BOARD_WIDTH * 18 + 150, BOARD_HEIGHT * 18}, "TETRIS++", sf::Style::Default }, m_Texture{}, m_SeparationLine{}, m_TetrisShape{ nullptr }, m_Preview{ nullptr },
	m_Board{}, m_Score{}, m_ElapsedTime{ sf::Time::Zero }, m_ID{ Utils::GetRandomNumber(7) }, m_GameplayMusic{}, m_pause{ false }, m_pauseMenu{}, m_fontOptions{}, m_textPauseMenu{}
{
	m_SeparationLine.setSize(sf::Vector2f{ 2.f, BOARD_HEIGHT * 18.f });
	m_SeparationLine.setPosition(sf::Vector2f{ BOARD_WIDTH * 18.f, 0 });
	m_SeparationLine.setFillColor(sf::Color::Red);

	m_pauseMenu.setSize(sf::Vector2f{ 250.f,150.f });
	m_pauseMenu.setFillColor(sf::Color(0, 250, 154));
	m_pauseMenu.setOutlineColor(sf::Color::White);
	m_pauseMenu.setOutlineThickness(4);
	m_pauseMenu.setPosition(sf::Vector2f{ (BOARD_WIDTH * 18 + 150) / 4.5,(BOARD_HEIGHT * 18) / 3 });

	if (!m_fontOptions.loadFromFile("arial.ttf"))
	{
		// error...
	}

	m_textPauseMenu[0].setFont(m_fontOptions);
	m_textPauseMenu[0].setFillColor(sf::Color(0, 191, 255));
	m_textPauseMenu[0].setOutlineColor(sf::Color::Black);
	m_textPauseMenu[0].setOutlineThickness(3);
	m_textPauseMenu[0].setCharacterSize(25);
	m_textPauseMenu[0].setString("Pause Menu");
	m_textPauseMenu[0].setPosition(sf::Vector2f((BOARD_WIDTH * 18 + 150) / 3.1, (BOARD_HEIGHT * 18) / 3));

	for (int i = 1;i < 4;i++)
	{
		m_textPauseMenu[i].setFont(m_fontOptions);
		m_textPauseMenu[i].setFillColor(sf::Color::White);
		m_textPauseMenu[i].setOutlineColor(sf::Color::Black);
		m_textPauseMenu[i].setOutlineThickness(3);
		m_textPauseMenu[i].setCharacterSize(15);
		m_textPauseMenu[i].setPosition(sf::Vector2f((BOARD_WIDTH * 18 + 150) / 3.3, (BOARD_HEIGHT * 18) / 3 + 40 * i));
	}
	m_textPauseMenu[1].setString("Press Enter for Continue");
	m_textPauseMenu[2].setString("Press O for Options");
	m_textPauseMenu[3].setString("Press Escape for Exit");

	if (!m_Texture.loadFromFile("Blocks.png"))
		std::cout << "Could not load texture from file !! \n";
	if (!m_GameplayMusic.openFromFile("Tetris.wav"))
		std::cout << "Could not load ~Tetris.wav~ from file!! \n";

	m_Board = std::make_unique<Board>(Position{ BOARD_WIDTH,BOARD_HEIGHT }, *this);
	CreateShape();
}

void Game::Run(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Clock clock; // starting the timer-ul
	sf::Time deltaTime(sf::Time::Zero);

	m_Board->Clean();

	m_GameplayMusic.play();
	m_GameplayMusic.setLoop(true);

	while (m_RenderWindow.isOpen())
	{
		m_GameplayMusic.setVolume((levelSound * 20.f));

		if (!m_pause)
		{
			sf::Time trigger(sf::seconds(85.f / (85.f + (m_Score.GetLevel() * (m_Score.GetLevel() * 5.f))))); // la inceput este = 1;
			std::cout << "Trigger =" << trigger.asMilliseconds() << std::endl;
			deltaTime = clock.restart(); // restarting the timer and returning the time passed until this point
			m_ElapsedTime += deltaTime;
			std::cout << "m_ElapsedTime = " << m_ElapsedTime.asMilliseconds() << std::endl << std::endl;

			ProcessEvents(menuOrGame, levelSound);
			Update(deltaTime);

			if (m_ElapsedTime > trigger)
			{
				m_ElapsedTime = sf::Time::Zero;
				Proceed(Direction::Down);
				std::cout << "Should go Down" << std::endl;
			}
			Render();
		}
		else {
			ProcessEvents(menuOrGame, levelSound);
			Render();
		}
	}
	m_GameplayMusic.stop();
}

void Game::Proceed(Direction direction)
{
	if (!m_TetrisShape)
		return;

	if (IsValidMovement(m_TetrisShape->GetFutureBlockPosition(direction)))
	{
		m_TetrisShape->Move(direction);
		if (direction == Direction::UserPressedDown)
			m_Score.AddPressedScore(1);
	}
	else
	{
		if (direction == Direction::Down || direction == Direction::UserPressedDown)
		{
			int id = m_TetrisShape->GetID();
			m_Board->AddBlock(id, m_TetrisShape->GetBlockPosition());
			m_TetrisShape.reset(nullptr);
			m_Score.SumPressedScore();
		}
	}
}

void Game::Update(const sf::Time& dt)
{
	m_Board->Update(dt);
	m_Score.Update(dt);
	if (!m_TetrisShape)
	{
		if (m_Board->IsToRemoveBlocks())
			return;
		CreateShape();
	}
}


void Game::Rotate()
{
	if (!m_TetrisShape)
		return;

	m_TetrisShape->Rotate();
	if (!IsValidMovement(m_TetrisShape->GetBlockPosition()))
		m_TetrisShape->RevertState();
}

void Game::ScaleUp()
{
	if (!m_TetrisShape)
		return;

	m_TetrisShape->ScaleUp();
	if (!IsValidMovement(m_TetrisShape->GetBlockPosition()))
	{
		m_TetrisShape->RevertState();
	}
}

void Game::ScaleDown()
{
	if (!m_TetrisShape)
		return;

	m_TetrisShape->ScaleDown();
	if (!IsValidMovement(m_TetrisShape->GetBlockPosition()))
	{
		m_TetrisShape->RevertState();
	}
}

void Game::CreateShape()
{
	m_TetrisShape.reset(new TetrisShape(m_Texture, m_ID));

	//create new game if necessary
	if (m_Board->IsOccupied(m_TetrisShape->GetBlockPosition()))
	{
		std::cout << "Game Over\n";

		sf::Music gameoverMusic;
		if (!gameoverMusic.openFromFile("gameover.wav"))
			std::cout << "Could not load ~gameover.wav~ from file !! \n";

		//m_GameplayMusic.stop();
		gameoverMusic.play();
		//system("pause");

		m_Score.Reset();
		m_Board->Clean();
		//m_GameplayMusic.play();
		m_pause = true;
	}

	m_ID = Utils::GetRandomNumber(7);
	m_Preview.reset(new TetrisShape(m_Texture, m_ID));
	m_Preview->SetPosition(sf::Vector2i{ BOARD_WIDTH,30 });
}

bool Game::IsValidMovement(std::array<Position, 16> block)
{
	for (int i = 0; i < 16; i++)
	{
		if (block[i].x < 0 || block[i].x > BOARD_WIDTH - 1 || block[i].y > BOARD_HEIGHT - 1)
		{
			std::cout << "INVALID" << std::endl;
			return false;
		}
		if (IsOccupied(block[i].x, block[i].y))
		{
			std::cout << "INVALID" << std::endl;
			return false;
		}
	}
	std::cout << "VALID" << std::endl;
	return true;
}

bool Game::IsOccupied(int x, int y)
{
	return m_Board->GetField(x, y)->m_Occupied;
}

void Game::ProcessEvents(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Event e;
	while (m_RenderWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			menuOrGame = 1;
			m_RenderWindow.close();
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			if (!m_pause)
			{
				if (e.key.code == sf::Keyboard::Down)
					Proceed(Direction::Down);
				else if (e.key.code == sf::Keyboard::Left)
					Proceed(Direction::Left);
				else if (e.key.code == sf::Keyboard::Right)
					Proceed(Direction::Right);
				else if (e.key.code == sf::Keyboard::Up)
					Rotate();
				else if (e.key.code == sf::Keyboard::A)
					ScaleUp();
				else if (e.key.code == sf::Keyboard::Z)
					ScaleDown();
				else if (e.key.code == sf::Keyboard::Escape)
				{
					menuOrGame = 1;
					m_RenderWindow.close();
				}
				else if (e.key.code == sf::Keyboard::Space)
				{
					m_pause = true;
				}
			}
			else
			{
				if (e.key.code == sf::Keyboard::Enter)
					m_pause = false;
				else if (e.key.code == sf::Keyboard::O)
				{
					Options options;
					options.RunOptions(levelSound);
				}
				else if (e.key.code == sf::Keyboard::Escape)
				{
					menuOrGame = 1;
					m_RenderWindow.close();
				}
			}
		}
	}
}

void Game::Render()
{
	m_RenderWindow.clear(sf::Color::Black);
	m_Score.Draw(m_RenderWindow);
	m_Board->Draw(m_RenderWindow);
	if (m_TetrisShape)
		m_RenderWindow.draw(*m_TetrisShape);
	m_RenderWindow.draw(*m_Preview);
	m_RenderWindow.draw(m_SeparationLine);
	if (m_pause)
	{
		m_RenderWindow.draw(m_pauseMenu);
		for (int i = 0;i < 4;i++)
			m_RenderWindow.draw(m_textPauseMenu[i]);
	}
	m_RenderWindow.display();
}
