#include "Highscore.h"
#include <fstream>
#include <sstream>
#include <set>

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

	//InitializeScorePlayerList();
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
		m_textModeGame.setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 5.2, HIGHSCORE_HEIGHT / 4.8));
		m_textModeGame.setString("MultiplayerCo-op");
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
				if (e.key.code == sf::Keyboard::Left)
				{
					if (m_modeGame > 0)
						m_modeGame--;
				}
				if (e.key.code == sf::Keyboard::Right)
				{
					if (m_modeGame < 1)
						m_modeGame++;
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
	m_textModeGame.setCharacterSize(25);

	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_playersList[i].setFont(m_fontHighscore);
		m_playersList[i].setFillColor(sf::Color(55, 205, 55));
		m_playersList[i].setOutlineColor(sf::Color::Black);
		m_playersList[i].setOutlineThickness(3);
		if (m_modeGame == 0)
		{
			m_playersList[i].setString("Unknown   0");
			m_playersList[i].setCharacterSize(19);
			m_playersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 3, HIGHSCORE_HEIGHT / 18 * i + 265));
		}
		else
		{
			m_playersList[i].setString("Unknown1&\n Unknown2  0");
			m_playersList[i].setCharacterSize(16);
			m_playersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 3, HIGHSCORE_HEIGHT / 17.5 * i + 250));
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
		auto cmp = [](std::pair<std::string, int> p1, std::pair<std::string, int> p2)
		{
			return p1.second > p2.second;
		};

		if (readFile.is_open())
		{
			std::string line;
			uint16_t index = 0;
			std::set<std::pair<std::string, int>, decltype(cmp)> playersSet(cmp);

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
				playersSet.insert(std::make_pair(name, score));
			}

			for (auto p : playersSet)
			{
				if (index < MAX_NUMBER_PLAYERS) {
					m_playersList[index].setString(p.first + std::to_string(p.second));
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
		if (readFile.is_open())
		{
			std::string line;
			uint16_t index = 0;
			std::vector<typePlayer> playersVector;
			for (std::string line; getline(readFile, line);)
			{
				std::istringstream wordbyword(line);
				std::string name1;
				std::string name2;
				std::string score;
				std::getline(wordbyword, name1, ' ');
				std::getline(wordbyword, name2, ' ');
				std::getline(wordbyword, score);
				while (name2.size() != 10)
					name2 += " ";
				std::string name;
				name = name1 + "&\n" + name2;
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
}