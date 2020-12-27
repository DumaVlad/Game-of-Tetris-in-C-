#include "Options.h"

Options::Options()
	: m_renderWindowOptions{ sf::VideoMode{OPTIONS_WIDTH, OPTIONS_HEIGHT}, "OPTIONS" }, m_page{ 1 }
{
	if (!m_textureOptions.loadFromFile("optionsTetrisEffect.jpg"))
	{
		// error..
	}

	if (!m_fontOptions.loadFromFile("arial.ttf"))
	{
		// error...
	}

	m_textureOptions.setSmooth(true);
	m_spriteOptions.setTexture(m_textureOptions);
	m_spriteOptions.setColor(sf::Color(255, 255, 255, 158));
	m_spriteOptions.setOrigin(0, 0);

	m_controlsSingleplayerGame[0].setFont(m_fontOptions);
	m_controlsSingleplayerGame[0].setFillColor(sf::Color::White);
	m_controlsSingleplayerGame[0].setOutlineColor(sf::Color::Black);
	m_controlsSingleplayerGame[0].setOutlineThickness(3);
	m_controlsSingleplayerGame[0].setCharacterSize(25);
	m_controlsSingleplayerGame[0].setString("Controls in SP game");
	m_controlsSingleplayerGame[0].setPosition(sf::Vector2f(OPTIONS_WIDTH / 12, OPTIONS_HEIGHT / 15));

	for (int i = 1;i < MAX_NUMBER_CONTROLS;i++)
	{
		m_controlsSingleplayerGame[i].setFont(m_fontOptions);
		m_controlsSingleplayerGame[i].setFillColor(sf::Color::White);
		m_controlsSingleplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsSingleplayerGame[i].setOutlineThickness(3);
		m_controlsSingleplayerGame[i].setCharacterSize(15);
		m_controlsSingleplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 8, OPTIONS_HEIGHT / 15 * (i + 1)));
	}

	m_controlsSingleplayerGame[1].setString("Arrow Down = piece go down");
	m_controlsSingleplayerGame[2].setString("Arrow Left = piece go left");
	m_controlsSingleplayerGame[3].setString("Arrow Right = piece go right");
	m_controlsSingleplayerGame[4].setString("Arrow Up = piece rotate");
	m_controlsSingleplayerGame[5].setString("A = piece scale up");
	m_controlsSingleplayerGame[6].setString("Z = piece scale down");
	m_controlsSingleplayerGame[7].setString("Escape = return to menu");
	m_controlsSingleplayerGame[8].setString("Space = pause game");


	m_controlsMultiplayerGame[0].setFont(m_fontOptions);
	m_controlsMultiplayerGame[0].setFillColor(sf::Color::White);
	m_controlsMultiplayerGame[0].setOutlineColor(sf::Color::Black);
	m_controlsMultiplayerGame[0].setOutlineThickness(3);
	m_controlsMultiplayerGame[0].setCharacterSize(25);
	m_controlsMultiplayerGame[0].setString("Controls in MP game");
	m_controlsMultiplayerGame[0].setPosition(sf::Vector2f(OPTIONS_WIDTH / 12, OPTIONS_HEIGHT / 15));

	m_controlsMultiplayerGame[1].setFont(m_fontOptions);
	m_controlsMultiplayerGame[1].setFillColor(sf::Color::White);
	m_controlsMultiplayerGame[1].setOutlineColor(sf::Color::Black);
	m_controlsMultiplayerGame[1].setOutlineThickness(3);
	m_controlsMultiplayerGame[1].setCharacterSize(20);
	m_controlsMultiplayerGame[1].setString("Player 1");
	m_controlsMultiplayerGame[1].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10, OPTIONS_HEIGHT / 15 * 2));

	m_controlsMultiplayerGame[2].setFont(m_fontOptions);
	m_controlsMultiplayerGame[2].setFillColor(sf::Color::White);
	m_controlsMultiplayerGame[2].setOutlineColor(sf::Color::Black);
	m_controlsMultiplayerGame[2].setOutlineThickness(3);
	m_controlsMultiplayerGame[2].setCharacterSize(20);
	m_controlsMultiplayerGame[2].setString("Player 2");
	m_controlsMultiplayerGame[2].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10 * 6, OPTIONS_HEIGHT / 15 * 2));

	for (int i = 3;i < MAX_NUMBER_CONTROLS_MP / 2 + 1;i++)
	{
		m_controlsMultiplayerGame[i].setFont(m_fontOptions);
		m_controlsMultiplayerGame[i].setFillColor(sf::Color::White);
		m_controlsMultiplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsMultiplayerGame[i].setOutlineThickness(3);
		m_controlsMultiplayerGame[i].setCharacterSize(15);
		m_controlsMultiplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10, OPTIONS_HEIGHT / 19 * (i + 1)));
	}

	for (int i = MAX_NUMBER_CONTROLS_MP / 2 + 1;i < MAX_NUMBER_CONTROLS_MP - 2;i++)
	{
		m_controlsMultiplayerGame[i].setFont(m_fontOptions);
		m_controlsMultiplayerGame[i].setFillColor(sf::Color::White);
		m_controlsMultiplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsMultiplayerGame[i].setOutlineThickness(3);
		m_controlsMultiplayerGame[i].setCharacterSize(15);
		m_controlsMultiplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10 * 6, OPTIONS_HEIGHT / 19 * (i - 6 + 1)));
	}

	for (int i = MAX_NUMBER_CONTROLS_MP - 2;i < MAX_NUMBER_CONTROLS_MP;i++)
	{
		m_controlsMultiplayerGame[i].setFont(m_fontOptions);
		m_controlsMultiplayerGame[i].setFillColor(sf::Color::White);
		m_controlsMultiplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsMultiplayerGame[i].setOutlineThickness(3);
		m_controlsMultiplayerGame[i].setCharacterSize(15);
		m_controlsMultiplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 3, OPTIONS_HEIGHT / 19 * (i - 6 + 1)));
	}

	m_controlsMultiplayerGame[3].setString("Arrow Down = piece go down");
	m_controlsMultiplayerGame[4].setString("Arrow Left = piece go left");
	m_controlsMultiplayerGame[5].setString("Arrow Right = piece go right");
	m_controlsMultiplayerGame[6].setString("Arrow Up = piece rotate");
	m_controlsMultiplayerGame[7].setString("Numpad1 = piece scale up");
	m_controlsMultiplayerGame[8].setString("Numpad0 = piece scale down");
	m_controlsMultiplayerGame[9].setString(" S = piece go down");
	m_controlsMultiplayerGame[10].setString(" A = piece go left");
	m_controlsMultiplayerGame[11].setString(" D = piece go right");
	m_controlsMultiplayerGame[12].setString(" W = piece rotate");
	m_controlsMultiplayerGame[13].setString(" R = piece scale up");
	m_controlsMultiplayerGame[14].setString(" F = piece scale down");
	m_controlsMultiplayerGame[15].setString("Escape = return to menu");
	m_controlsMultiplayerGame[16].setString("Space = pause game");


	for (int i = 0;i < 6;i++)
	{
		m_controlSound[i].setFont(m_fontOptions);
		m_controlSound[i].setFillColor(sf::Color::Red);
		m_controlSound[i].setOutlineColor(sf::Color::Black);
		m_controlSound[i].setOutlineThickness(5);
		m_controlSound[i].setCharacterSize(25);
		m_controlSound[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 12, OPTIONS_HEIGHT / 15 * 12));
	}

	m_controlSound[0].setString("Sound mute");
	m_controlSound[1].setString("Sound 20%");
	m_controlSound[2].setString("Sound 40%");
	m_controlSound[3].setString("Sound 60%");
	m_controlSound[4].setString("Sound 80%");
	m_controlSound[5].setString("Sound 100%");
}

void Options::draw(uint16_t& levelSound)
{
	if (m_page == 1)
		for (int i = 0; i < MAX_NUMBER_CONTROLS; i++)
		{
			m_renderWindowOptions.draw(m_controlsSingleplayerGame[i]);
		}
	else
		for (int i = 0; i < MAX_NUMBER_CONTROLS_MP; i++)
		{
			m_renderWindowOptions.draw(m_controlsMultiplayerGame[i]);
		}
	m_renderWindowOptions.draw(m_controlSound[levelSound]);
}

void Options::RunOptions(uint16_t& levelSound)
{
	while (m_renderWindowOptions.isOpen())
	{
		sf::Event e;
		while (m_renderWindowOptions.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_renderWindowOptions.close();
			}
			else if (e.type == sf::Event::KeyPressed)
			{

				if (e.key.code == sf::Keyboard::Escape)
				{
					m_renderWindowOptions.close();
				}
				if (e.key.code == sf::Keyboard::Up)
				{
					if (levelSound < 5)
						levelSound++;
				}
				if (e.key.code == sf::Keyboard::Down)
				{
					if (levelSound > 0)
						levelSound--;
				}
				if (e.key.code == sf::Keyboard::Left)
				{
					if (m_page > 1)
						m_page--;
				}
				if (e.key.code == sf::Keyboard::Right)
				{
					if (m_page < 2)
						m_page++;
				}
			}
		}
		m_renderWindowOptions.clear();
		m_renderWindowOptions.draw(m_spriteOptions);
		draw(levelSound);
		m_renderWindowOptions.display();
	}
}

Options::~Options()
{
}
