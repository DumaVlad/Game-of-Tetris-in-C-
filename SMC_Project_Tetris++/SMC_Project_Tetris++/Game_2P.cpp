#include "Game_2P.h"
#include "Utils.h"
#include "Menu.h"
#include "Options.h"
#include "Highscore.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>

Game_2P::Game_2P()
	: IGame(BOARD_WIDTH_2P, BOARD_HEIGHT_2P), m_ID_2P{ Utils::GetRandomNumber(7) }, m_tetrisShape_2P{ nullptr }, m_preview_2P{ nullptr }
{
	if (!m_backGroundTexture.loadFromFile("../Resources/Images/tetris_board2P.jpg"))
	{
		std::cout << "Could not load texture from file in IGame !! \n";
	}
	m_backGroundTexture.setSmooth(true);
	m_backGroundSprite.setTexture(m_backGroundTexture);
	m_backGroundSprite.setColor(sf::Color(255, 255, 255, 160));
	m_backGroundSprite.setOrigin(0, 0);

	m_pauseMenu.setSize(sf::Vector2f{ 430.f,200.f });

	m_board = std::make_unique<Board_2P>(Position{ BOARD_WIDTH_2P,BOARD_HEIGHT_2P }, *this);
	CreateShape();
	CreateShape_2P();
}

void Game_2P::Run(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Clock clock; // starting the timer-ul
	sf::Time deltaTime(sf::Time::Zero);

	m_board->Clean();

	m_gameplayMusic.play();
	m_gameplayMusic.setLoop(true);

	auto start = std::chrono::system_clock::now();
	auto randomTime = Utils::GetRandomNumber(10, 20);

	while (m_renderWindow.isOpen())
	{
		m_gameplayMusic.setVolume(levelSound * 20.f);

		if (!m_pause)
		{
			sf::Time trigger(sf::seconds(85.f / (85.f + (m_player->GetLevel() * (m_player->GetLevel() * 5.f))))); // la inceput este = 1;
			std::cout << "Trigger =" << trigger.asMilliseconds() << std::endl;
			deltaTime = clock.restart(); // restarting the timer and returning the time passed until this point
			m_elapsedTime += deltaTime;
			std::cout << "m_ElapsedTime = " << m_elapsedTime.asMilliseconds() << std::endl << std::endl;

			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> duration = end - start;
			if (duration.count() >= randomTime)
			{
				std::cout << std::endl << duration.count();
				start = std::chrono::system_clock::now();
				AddSpecialShape();
				randomTime = Utils::GetRandomNumber(40, 120);
				std::cout << std::endl << randomTime;
			}

			ProcessEvents(menuOrGame, levelSound);
			Update(deltaTime);

			if (m_elapsedTime > trigger)
			{
				m_elapsedTime = sf::Time::Zero;
				Proceed(Direction::Down);
				Proceed_2P(Direction::Down);
				std::cout << "Should go Down" << std::endl;
			}
			Render();
		}
		else
		{
			ProcessEvents(menuOrGame, levelSound);
			Render();
		}
	}
	m_gameplayMusic.stop();
}

void Game_2P::Proceed(Direction direction)
{
	IGame::Proceed(direction);
}

void Game_2P::Proceed_2P(Direction direction)
{
	if (!m_tetrisShape_2P)
		return;

	if (IsValidMovement(m_tetrisShape_2P->GetFutureBlockPosition(direction)))
	{
		m_tetrisShape_2P->Move(direction);
		if (direction == Direction::UserPressedDown)
			m_player->AddPressedScore(1);
	}
	else
	{
		if (direction == Direction::Down || direction == Direction::UserPressedDown)
		{
			int id = m_tetrisShape_2P->GetID();
			m_board->AddBlock(id, m_tetrisShape_2P->GetBlockPosition());
			m_tetrisShape_2P.reset(nullptr);
			m_player->SumPressedScore();
		}
	}
}

void Game_2P::Update(const sf::Time& dt)
{
	m_board->Update(dt);
	m_player->Update(dt);
	if (!m_tetrisShape)
	{
		if (m_board->IsToRemoveBlocks())
			return;
		CreateShape();
	}
	if (!m_tetrisShape_2P)
	{
		if (m_board->IsToRemoveBlocks())
			return;
		CreateShape_2P();
	}

}

void Game_2P::Rotate()
{
	IGame::Rotate();
}

void Game_2P::Rotate_2P()
{
	if (!m_tetrisShape_2P)
		return;

	TetrisShape temp = *m_tetrisShape_2P;
	temp.Rotate();
	if (!IsValidMovement(temp.GetBlockPosition()))
		return;
	else
		m_tetrisShape_2P->Rotate();
}

void Game_2P::ScaleUp()
{
	IGame::ScaleUp();
}

void Game_2P::ScaleUp_2P()
{
	if (!m_tetrisShape_2P)
		return;

	TetrisShape temp = *m_tetrisShape_2P;
	temp.ScaleUp();
	if (!IsValidMovement(temp.GetBlockPosition()))
		return;
	else
		m_tetrisShape_2P->ScaleUp();
}

void Game_2P::ScaleDown()
{
	IGame::ScaleDown();
}

void Game_2P::ScaleDown_2P()
{
	if (!m_tetrisShape_2P)
		return;

	TetrisShape temp = *m_tetrisShape_2P;
	temp.ScaleDown();
	if (!IsValidMovement(temp.GetBlockPosition()))
		return;
	else
		m_tetrisShape_2P->ScaleDown();
}

void Game_2P::AddSpecialShape()
{
	std::pair<uint16_t, uint16_t> field = GetFreePosition(Utils::GetRandomNumber(0, BOARD_WIDTH_2P - 1), BOARD_HEIGHT_2P);
	Position block(field.first, field.second);
	m_board->AddSpecialBlock(Utils::GetRandomNumber(0, 6), block);
	return;
}

void Game_2P::CreateShape()
{
	m_tetrisShape.reset(new TetrisShape(m_texture, m_ID, STARTING_POSITION_1P));
	//create new game if necessary
	if (m_board->IsOccupied(m_tetrisShape->GetBlockPosition()))
	{
		std::cout << "Game Over" << std::endl;

		sf::Music gameoverMusic;
		if (!gameoverMusic.openFromFile("../Resources/Sounds/gameover.wav"))
			std::cout << "Could not load the gameover sound from file !! \n";
		FileWriter("../Resources/Files/outputPlayers2Pcoop.txt");

		m_gameplayMusic.stop();
		gameoverMusic.play();

		m_board->Clean();
		m_gameplayMusic.play();
		m_pause = 2;
	}
	m_ID = Utils::GetRandomNumber(7);
	m_preview.reset(new TetrisShape(m_texture, m_ID, STARTING_POSITION_1P));
	m_preview->SetPosition(Position{ BOARD_WIDTH_2P, 30 });
}

void Game_2P::CreateShape_2P()
{
	m_tetrisShape_2P.reset(new TetrisShape(m_texture, m_ID_2P, STARTING_POSITION_2P));
	//create new game if necessary
	if (m_board->IsOccupied(m_tetrisShape_2P->GetBlockPosition()))
	{
		std::cout << "Game Over" << std::endl;

		sf::Music gameoverMusic;
		if (!gameoverMusic.openFromFile("../Resources/Sounds/gameover.wav"))
			std::cout << "Could not load the gameover sound from file !! \n";
		FileWriter("../Resources/Files/outputPlayers2Pcoop.txt");

		m_gameplayMusic.stop();
		gameoverMusic.play();

		//system("pause");

		m_board->Clean();
		m_gameplayMusic.play();
		m_pause = 2;
	}
	m_ID_2P = Utils::GetRandomNumber(7);
	m_preview_2P.reset(new TetrisShape(m_texture, m_ID_2P, STARTING_POSITION_2P));
	m_preview_2P->SetPosition(Position{ BOARD_WIDTH_2P, 0 });
}

bool Game_2P::IsValidMovement(std::array<Position, BLOCK_ARRAY_COLUMNS> block)
{
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		if (block[i].x < 0 || block[i].x > BOARD_WIDTH_2P - 1 || block[i].y > BOARD_HEIGHT_2P - 1)
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

bool Game_2P::IsOccupied(uint16_t x, uint16_t y)
{
	return IGame::IsOccupied(x, y);
}

void Game_2P::ProcessEvents(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Event e;
	while (m_renderWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			menuOrGame = 1;
			m_renderWindow.close();
		}

		if (m_pause == 3 || m_pause == 4) {
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode == 13)
				{
					if (m_pause == 4)
						m_pause = 0;
					else
						m_pause = 4;
				}
				if (m_pause == 3)
				{
					if (e.text.unicode == 8 && !m_playerNameInput1.isEmpty())
					{
						m_playerNameInput1.erase(m_playerNameInput1.getSize() - 1, 1);
						m_playerNameText.setString(m_playerNameInput1);
					}
					else if (e.text.unicode > 64 && e.text.unicode < 91 || e.text.unicode > 96 && e.text.unicode < 123)
					{
						if (m_playerNameInput1.getSize() < 9)
							m_playerNameInput1 += e.text.unicode;
						m_playerNameText.setString(m_playerNameInput1);
					}
				}
				else
				{
					m_playerNameText.setString("");

					if (e.text.unicode == 8 && !m_playerNameInput2.isEmpty())
					{
						m_playerNameInput2.erase(m_playerNameInput2.getSize() - 1, 1);
						m_playerNameText.setString(m_playerNameInput2);
					}
					else if (e.text.unicode > 64 && e.text.unicode < 91 || e.text.unicode > 96 && e.text.unicode < 123)
					{
						if (m_playerNameInput2.getSize() < 9)
							m_playerNameInput2 += e.text.unicode;
						m_playerNameText.setString(m_playerNameInput2);
					}
				}
			}
			m_renderWindow.draw(m_playerNameText);
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			if (!m_pause)
			{
				if (e.key.code == sf::Keyboard::Down)
					Proceed(Direction::Down);
				else if (e.key.code == sf::Keyboard::S)
					Proceed_2P(Direction::Down);
				else if (e.key.code == sf::Keyboard::Left)
					Proceed(Direction::Left);
				else if (e.key.code == sf::Keyboard::A)
					Proceed_2P(Direction::Left);
				else if (e.key.code == sf::Keyboard::Right)
					Proceed(Direction::Right);
				else if (e.key.code == sf::Keyboard::D)
					Proceed_2P(Direction::Right);
				else if (e.key.code == sf::Keyboard::Up)
					Rotate();
				else if (e.key.code == sf::Keyboard::W)
					Rotate_2P();
				else if (e.key.code == sf::Keyboard::Numpad1)
					ScaleUp();
				else if (e.key.code == sf::Keyboard::R)
					ScaleUp_2P();
				else if (e.key.code == sf::Keyboard::Numpad0)
					ScaleDown();
				else if (e.key.code == sf::Keyboard::F)
					ScaleDown_2P();
				else if (e.key.code == sf::Keyboard::Escape)
				{
					menuOrGame = 1;
					m_renderWindow.close();
				}
				else if (e.key.code == sf::Keyboard::Space)
					m_pause = 1;
			}
			else
			{
				if (e.key.code == sf::Keyboard::Enter)
					m_pause = 0;
				else if (e.key.code == sf::Keyboard::O)
				{
					Options options;
					options.RunOptions(levelSound);
				}
				else if (e.key.code == sf::Keyboard::H)
				{
					Highscore highscore;
					highscore.runHighscore();
				}
				else if (e.key.code == sf::Keyboard::Escape)
				{
					menuOrGame = 1;
					m_renderWindow.close();
				}
			}
		}
	}
}

void Game_2P::Render()
{
	if (m_pause == 0)
	{
		m_renderWindow.clear(sf::Color::Black);
		m_renderWindow.draw(m_backGroundSprite);
		m_player->Draw(m_renderWindow);
		m_board->Draw(m_renderWindow);
		if (m_tetrisShape)
			m_renderWindow.draw(*m_tetrisShape);
		if (m_tetrisShape_2P)
			m_renderWindow.draw(*m_tetrisShape_2P);
		m_renderWindow.draw(*m_preview);
		m_renderWindow.draw(*m_preview_2P);
		m_renderWindow.draw(m_separationLine);
	}
	else if (m_pause == 1)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (uint16_t i = 0;i < 4;i++)
			m_renderWindow.draw(m_textPauseMenu[i]);
	}
	else if (m_pause == 2)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (uint16_t i = 0;i < 5;i++)
			m_renderWindow.draw(m_textGameOverMenu[i]);
	}
	else if (m_pause == 3)
	{
		m_playerNameBox.setString("Insert your name (player1):");
		m_renderWindow.draw(m_pauseMenu);
		m_renderWindow.draw(m_playerNameBox);
		m_renderWindow.draw(m_playerNameText);
		m_player = std::make_unique<Player>(m_playerNameInput1, BOARD_WIDTH_2P, BOARD_HEIGHT_2P);
	}
	else if (m_pause == 4)
	{
		m_playerNameBox.setString("Insert your name (player2):");
		m_renderWindow.draw(m_pauseMenu);
		m_renderWindow.draw(m_playerNameBox);
		m_renderWindow.draw(m_playerNameText);
		m_player2 = std::make_unique<Player>(m_playerNameInput2, BOARD_WIDTH_2P, BOARD_HEIGHT_2P);
	}
	m_renderWindow.display();
}

void Game_2P::FileWriter(const std::string& file)
{
	std::fstream fileOut;
	fileOut.open(file, std::fstream::app);
	if (!fileOut.is_open())
	{
		std::cout << "File cannot be opened!\n";
		return;
	}
	fileOut << m_player->GetPlayerName() << " " << m_player2->GetPlayerName() << " " << m_player->GetScore() << "\n";
}
