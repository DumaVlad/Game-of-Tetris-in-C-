#include "Player.h"
#include"Utils.h"

Player::Player(const std::string& playerName)
    : m_playerId{}, m_playerName{ playerName }
{
    m_playerId = Utils::GetRandomNumber(100);

}

uint16_t Player::GetplayerId()
{
    return m_playerId;
}
