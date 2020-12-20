#pragma once
#include<cstdint>
#include<string>
#include"Score.h"

class Player
{
public:

	Player(const std::string& playerName);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	std::string GetPlayerName();
	uint16_t GetScore();

	Score m_score;
private:
	std::string m_playerName;

};


