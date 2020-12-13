#include "Options.h"

Options::Options()
	: m_renderWindowOptions{ sf::VideoMode{OPTIONS_WIDTH, OPTIONS_HEIGHT}, "OPTIONS" }
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

	m_controlsGame[0].setFont(m_fontOptions);
	m_controlsGame[0].setFillColor(sf::Color::White);
	m_controlsGame[0].setOutlineColor(sf::Color::Black);
	m_controlsGame[0].setOutlineThickness(3);
	m_controlsGame[0].setCharacterSize(25);
	m_controlsGame[0].setString("Controls in game");
	m_controlsGame[0].setPosition(sf::Vector2f(OPTIONS_WIDTH / 12, OPTIONS_HEIGHT / 15));

	for (int i = 1;i < MAX_NUMBER_CONTROLS;i++)
	{
		m_controlsGame[i].setFont(m_fontOptions);
		m_controlsGame[i].setFillColor(sf::Color::White);
		m_controlsGame[i].setOutlineColor(sf::Color::Black);
		m_controlsGame[i].setOutlineThickness(3);
		m_controlsGame[i].setCharacterSize(15);
		m_controlsGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 8, OPTIONS_HEIGHT / 15 * (i + 1)));
	}

	m_controlsGame[1].setString("Arrow Down = piece go down");
	m_controlsGame[2].setString("Arrow Left = piece go left");
	m_controlsGame[3].setString("Arrow Right = piece go right");
	m_controlsGame[4].setString("Arrow Up = piece rotate");
	m_controlsGame[5].setString("A = piece scale up");
	m_controlsGame[6].setString("Z = piece scale down");
	m_controlsGame[7].setString("Escape = return to menu");
}

void Options::draw()
{
	for (int i = 0; i < MAX_NUMBER_CONTROLS; i++)
	{
		m_renderWindowOptions.draw(m_controlsGame[i]);
	}
}

void Options::RunOptions()
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
			}
		}
		m_renderWindowOptions.clear();
		m_renderWindowOptions.draw(m_spriteOptions);
		draw();
		m_renderWindowOptions.display();
	}
}

Options::~Options()
{
}
