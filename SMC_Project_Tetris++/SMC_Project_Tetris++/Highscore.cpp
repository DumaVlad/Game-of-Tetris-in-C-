#include "Highscore.h"
#include <fstream>
#include <sstream>
#include <map>

Highscore::Highscore(uint16_t modeGame)
	:m_renderWindowHighscore{ sf::VideoMode{HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT}, "HIGHSCORE" }, m_modeGame{ modeGame }
{
	if (!m_textureHighscore.loadFromFile("../Resources/Images/highscore.png"))
		std::cout << "Could not load image in Highscore Class !! \n";

	if (!m_fontHighscore.loadFromFile("../Resources/Fonts/arcade_i.ttf"))
		std::cout << "Could not load font in Highscore class !! \n";

	m_textureHighscore.setSmooth(true);
	m_spriteHighscore.setTexture(m_textureHighscore);
	//m_spriteHighscore.setColor(sf::Color(255, 255, 255, 200));
	m_spriteHighscore.setOrigin(0, 0);
}

void Highscore::draw()
{
	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_renderWindowHighscore.draw(m_playersList[i]);
	}
	if (m_modeGame == 0)
	{
		m_textModeGame.setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 4, HIGHSCORE_HEIGHT / 4.8));
		m_textModeGame.setString("Singleplayer");
	}
	else
	{
		m_textModeGame.setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 3.6, HIGHSCORE_HEIGHT / 4.8));
		m_textModeGame.setString("Multiplayer");
	}
	m_renderWindowHighscore.draw(m_textModeGame);
}

void Highscore::runHighscore()
{
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
		FileReader();
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
	m_textModeGame.setCharacterSize(30);

	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_playersList[i].setFont(m_fontHighscore);
		m_playersList[i].setFillColor(sf::Color(55, 205, 55));
		m_playersList[i].setOutlineColor(sf::Color::Black);
		m_playersList[i].setOutlineThickness(3);
		if (m_modeGame == 0)
		{
			m_playersList[i].setString("Unknown   0");
			m_playersList[i].setCharacterSize(20);
			m_playersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 2.9, HIGHSCORE_HEIGHT / 17.7 * i + 295));
		}
		else
		{
			m_playersList[i].setString("Unknown1&\n Unknown2   0");
			m_playersList[i].setCharacterSize(18);
			m_playersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 2.9, HIGHSCORE_HEIGHT / 18 * i + 290));
		}
	}

	m_playersList[0].setFillColor(sf::Color::Red);
	m_playersList[1].setFillColor(sf::Color(128, 0, 128));
	m_playersList[2].setFillColor(sf::Color(210, 89, 75));
	m_playersList[3].setFillColor(sf::Color(255, 165, 0));
	m_playersList[4].setFillColor(sf::Color::Yellow);
}


void Highscore::FileReader()
{
	if (m_modeGame == 0)
	{
		InitializeScorePlayerList();
		std::ifstream readFile("../Resources/Files/outputPlayers1P.txt");
		auto cmp = [](const int& left, const int& right) -> bool
		{
			return left > right;
		};

		if (readFile.is_open())
		{
			std::string line;
			uint16_t index = 0;
			std::map<std::string, int> tempMap;
			std::multimap<int, std::string, decltype(cmp)> playerScoreMap(cmp);

			while (!readFile.eof())
			{
				std::string line;
				std::getline(readFile, line);
				std::string name;
				int score;
				std::istringstream ss(line);
				ss >> name >> score;
				while (name.size() != 10)
					name += " ";
				if (tempMap.find(name) != tempMap.end())
				{
					if (tempMap[name] < score)
						tempMap[name] = score;
				}
				else
					tempMap.emplace(name, score);
			}

			for (auto p : tempMap)
				playerScoreMap.emplace(p.second, p.first);
			
			for (auto p : playerScoreMap) 
			{
				if (index < MAX_NUMBER_PLAYERS)
				{
					m_playersList[index].setString(p.second + std::to_string(p.first));
					index++;
				}
			}
			readFile.close();
		}
		else
			std::cout << "File was not open!";
	}
	else
	{
		InitializeScorePlayerList();
		std::ifstream readFile("../Resources/Files/outputPlayers2Pcoop.txt");
		auto cmp = [](const int& left, const int& right) -> bool
		{
			return left > right;
		};

		if (readFile.is_open())
		{
			std::string line;
			uint16_t index = 0;
			std::map<std::string, int> tempMap;
			std::multimap<int, std::string, decltype(cmp)> playerScoreMap(cmp);

			while (!readFile.eof())
			{
				std::string line;
				std::getline(readFile, line);
				std::string name1;
				std::string name2;
				int score;
				std::istringstream ss(line);
				ss >> name1 >> name2 >> score;
				while (name2.size() != 12)
					name2 += " ";
				std::string name = name1 + "&\n" + name2;
				if (tempMap.find(name) != tempMap.end())
				{
					if (tempMap[name] < score)
						tempMap[name] = score;
				}
				else
					tempMap.emplace(name, score);
			}

			for (auto p : tempMap)
				playerScoreMap.emplace(p.second, p.first);

			for (auto p : playerScoreMap)
			{
				if (index < MAX_NUMBER_PLAYERS) {
					m_playersList[index].setString(p.second + std::to_string(p.first));
					index++;
				}
			}
			readFile.close();
		}
		else
			std::cout << "File was not open!";
	}
}