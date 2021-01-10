#include "Highscore.h"
#include <fstream>

Highscore::Highscore()
	:m_renderWindowHighscore{ sf::VideoMode{HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT}, "HIGHSCORE" }
{
	if (!m_textureHighscore.loadFromFile("../Resources/Images/highscore.png"))
		std::cout << "Could not load image in Highscore Class !! \n";

	if (!m_fontHighscore.loadFromFile("../Resources/Fonts/arcade_i.ttf"))
		std::cout << "Could not load font in Highscore class !! \n";

	m_textureHighscore.setSmooth(true);
	m_spriteHighscore.setTexture(m_textureHighscore);
	//m_spriteHighscore.setColor(sf::Color(255, 255, 255, 200));
	m_spriteHighscore.setOrigin(0, 0);

	InitializeScorePlayerList();
}

void Highscore::draw()
{
	for (int i = 0; i < MAX_NUMBER_NAMES; i++)
	{
		m_renderWindowHighscore.draw(m_scorePlayersList[i]);
	}
}

void Highscore::runHighscore()
{
	FileReader();
	while (m_renderWindowHighscore.isOpen())
	{
		sf::Event e;
		while (m_renderWindowHighscore.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_renderWindowHighscore.close();
			}
		}
		m_renderWindowHighscore.clear();
		m_renderWindowHighscore.draw(m_spriteHighscore);
		draw();
		m_renderWindowHighscore.display();
	}
}

void Highscore::InitializeScorePlayerList()
{
	for (int i = 0; i < MAX_NUMBER_NAMES; i++)
	{
		m_scorePlayersList[i].setFont(m_fontHighscore);
		m_scorePlayersList[i].setFillColor(sf::Color::White);
		m_scorePlayersList[i].setOutlineColor(sf::Color::Black);
		m_scorePlayersList[i].setOutlineThickness(3);
		m_scorePlayersList[i].setCharacterSize(20);
		m_scorePlayersList[i].setString("");
		m_scorePlayersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 3, HIGHSCORE_HEIGHT / 18 * i + 265));
	}
}


void Highscore::FileReader()
{
	std::ifstream readFile("out.txt");
	if (readFile.is_open())
	{
		std::string line;
		uint16_t index = 0;
		for (std::string line; getline(readFile, line);)
		{
			if (index < MAX_NUMBER_NAMES)
			{
				m_scorePlayersList[index].setString(line);
				index++;
			}
		}
		readFile.close();
	}
	else
		std::cout << "File was not open!";
}
