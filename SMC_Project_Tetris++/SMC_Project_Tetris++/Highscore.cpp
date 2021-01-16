#include "Highscore.h"
#include <fstream>
#include <sstream>

Highscore::Highscore()
	:m_renderWindowHighscore{ sf::VideoMode{HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT}, "HIGHSCORE" }, m_modeGame{ 0 }
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
	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_renderWindowHighscore.draw(m_playersList[i]);
	}
	m_renderWindowHighscore.draw(m_textModeGame);
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
			else if (e.type == sf::Event::KeyPressed)
			{

				if (e.key.code == sf::Keyboard::Escape)
				{
					m_renderWindowHighscore.close();
				}
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
	m_textModeGame.setFont(m_fontHighscore);
	m_textModeGame.setFillColor(sf::Color::Blue);
	m_textModeGame.setOutlineColor(sf::Color::White);
	m_textModeGame.setOutlineThickness(3);
	m_textModeGame.setCharacterSize(25);
	m_textModeGame.setString("Singleplayer");
	m_textModeGame.setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 4, HIGHSCORE_HEIGHT / 4.8));

	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_playersList[i].setFont(m_fontHighscore);
		m_playersList[i].setFillColor(sf::Color(55, 205, 55));
		m_playersList[i].setOutlineColor(sf::Color::Black);
		m_playersList[i].setOutlineThickness(3);
		m_playersList[i].setCharacterSize(19);
		m_playersList[i].setString("Unknown   0");
		m_playersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 3, HIGHSCORE_HEIGHT / 18 * i + 265));
	}

	m_playersList[0].setFillColor(sf::Color::Red);
	m_playersList[1].setFillColor(sf::Color(128, 0, 128));
	m_playersList[2].setFillColor(sf::Color(210, 89, 75));
	m_playersList[3].setFillColor(sf::Color(255, 165, 0));
	m_playersList[4].setFillColor(sf::Color::Yellow);
}


void Highscore::FileReader()
{
	std::ifstream readFile("../Resources/Files/outputPlayers1P.txt");
	if (readFile.is_open())
	{
		std::string line;
		uint16_t index = 0;
		std::vector<typePlayer> playersVector;
		for (std::string line; getline(readFile, line);)
		{
			std::istringstream wordbyword(line);
			std::string name;
			std::string score;
			std::getline(wordbyword, name, ' ');
			std::getline(wordbyword, score);
			while (name.size() != 10)
				name += " ";
			typePlayer player;
			player.first = name;
			player.second = score;
			bool find = false;
			for (typePlayer& playerIndex : playersVector)
				if (playerIndex.first.compare(player.first) == 0)
				{
					if (std::stoi(player.second) > std::stoi(playerIndex.second))
						playerIndex.second = player.second;
					find = true;
				}

			if (!find)
				playersVector.push_back(player);
		}

		std::sort(playersVector.begin(), playersVector.end(), m_comparePlayers);

		for (typePlayer player : playersVector)
			if (index < MAX_NUMBER_PLAYERS)
			{
				m_playersList[index].setString(playersVector.at(index).first + playersVector.at(index).second);
				index++;
			}
			else
				break;

		readFile.close();
	}
	else
		std::cout << "File was not open!";
}