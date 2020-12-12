#pragma once
#include<cstdint>
#include<string>

class Player
{
public:

	Player(const std::string& playerName);
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	uint16_t GetplayerId();
private:
	uint16_t m_playerId;
	std::string m_playerName;
};

