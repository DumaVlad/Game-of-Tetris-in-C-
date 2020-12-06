#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game()
	: m_RenderWindow{ sf::VideoMode{600, 600}, "TETRIS", sf::Style::Default }, m_Texture{}, m_SeparationLine{}, m_TetrisShape{ nullptr }, m_Preview{ nullptr }, m_Board{}, m_ElapsedTime{ sf::Time::Zero }, m_ID{ Utils::GetRandomNumber(7) }
{
	m_SeparationLine.setSize(sf::Vector2f{ 1.f, 18.f * 18.f });
	m_SeparationLine.setPosition(sf::Vector2f{ 10.f * 18.f, 0 });
	m_SeparationLine.setFillColor(sf::Color::Red);
	if (!m_Texture.loadFromFile("Blocks.png"))
	{
		std::cout << "Could not load texture from file !! \n";
	}
	m_Board = std::make_unique<Board>(Position{ 10,18 }, *this);
	CreateShape();
}

void Game::Run()
{


	sf::Clock clock; // turn on the timer
	//std::cout << clock.getElapsedTime().asMilliseconds() << " -> ";
	sf::Time deltaTime(sf::Time::Zero);
	//std::cout << clock.getElapsedTime().asMilliseconds() << " -> ";

	sf::Texture textureMenu;
	sf::Texture textureShape;
	sf::Sprite spriteMenu;
	bool menuOrGame = 1; // 1 for Menu, 0 for Game

	if (!textureMenu.loadFromFile("tetris600x600.jpg"))
	{
		std::cout << "Can't load the texture from the file !" << std::endl;
	}

	textureMenu.setSmooth(true);
	spriteMenu.setTexture(textureMenu);
	spriteMenu.setOrigin(0, 0);

	Menu menu(m_RenderWindow.getSize().x, m_RenderWindow.getSize().y);

	while (m_RenderWindow.isOpen())
	{
		if (menuOrGame)
		{
			sf::Event event;
			while (m_RenderWindow.pollEvent(event))
			{
				switch (event.type)
				{
				case::sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed!" << std::endl;
							menuOrGame = 0;
							break;
						case 1:
							std::cout << "Options button has been pressed!" << std::endl;
							break;
						case 2:
							m_RenderWindow.close();
							break;
						}
						break;
					}
					break;
				case sf::Event::Closed:
					m_RenderWindow.close();
					break;
				}
			}
		}
		else
		{
			//it is only used temporarily for test
			const uint16_t testScore = 10;
			sf::Time trigger(sf::seconds(85.f / (85.f + (testScore * (testScore * 5.f))))); // at the beginning it is 1
			//std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
			deltaTime = clock.restart(); // The timer is restarted and the time from the last restart is returned
			m_ElapsedTime += deltaTime;
			ProcessEvents();
			Update(deltaTime);
			if (m_ElapsedTime > trigger) {
				m_ElapsedTime = sf::Time::Zero;
				Proceed(Direction::Down);
			}
			Render();
		}
		m_RenderWindow.clear();
		if (menuOrGame)
		{
			m_RenderWindow.draw(spriteMenu);
			menu.draw(m_RenderWindow);
		}
		m_RenderWindow.display();
	}
}

void Game::Proceed(Direction direction)
{
	if (!m_TetrisShape)
		return;

	if (!IsValidMovement(m_TetrisShape->GetFutureBlockPosition(direction)))
	{
		m_TetrisShape->Move(direction);
	}
	else
	{
		if (direction == Direction::Down || direction == Direction::UserPressedDown)
		{
			int id = m_TetrisShape->GetID();
			m_Board->AddBlock(id, m_TetrisShape->GetBlockPosition());
			m_TetrisShape.reset(nullptr);

		}
	}
}

void Game::Update(const sf::Time& dt)
{
	m_Board->Update(dt);
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
		m_Board->Clean();
	}
	m_ID = Utils::GetRandomNumber(7);
	m_Preview.reset(new TetrisShape(m_Texture, m_ID));
	m_Preview->SetPosition(sf::Vector2i{ 11,12 });
}

bool Game::IsValidMovement(std::array<Position, 16> block)
{
	for (int i = 0; i < 9; i++)
	{
		if (block[i].x < 0 || block[i].x > 9 || block[i].y > 17)
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

void Game::ProcessEvents()
{
	sf::Event e;
	while (m_RenderWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_RenderWindow.close();
		else if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Down)
				Proceed(Direction::Down);
			else if (e.key.code == sf::Keyboard::Left)
				Proceed(Direction::Left);
			else if (e.key.code == sf::Keyboard::Right)
				Proceed(Direction::Right);
			else if (e.key.code == sf::Keyboard::Space)
				Rotate();
			else if (e.key.code == sf::Keyboard::A)
				ScaleUp();
			else if (e.key.code == sf::Keyboard::Z)
				ScaleDown();
			else if (e.key.code == sf::Keyboard::P)
				m_Board->PrintBoard();
		}
	}
}

void Game::Render()
{
	m_RenderWindow.clear(sf::Color::Black);
	m_Board->Draw(m_RenderWindow);
	if (m_TetrisShape)
		m_RenderWindow.draw(*m_TetrisShape);
	m_RenderWindow.draw(*m_Preview);
	m_RenderWindow.draw(m_SeparationLine);
	m_RenderWindow.display();
}
