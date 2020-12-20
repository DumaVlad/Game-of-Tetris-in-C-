#include "Player.h"
#include"Utils.h"

Player::Player(const std::string& playerName)
  : m_playerName{ playerName }, m_score{ 10,10 }
{
}

std::string Player::GetPlayerName()
{
    return m_playerName;
}

uint16_t Player::GetScore()
{
    return m_score.GetScore();
}

