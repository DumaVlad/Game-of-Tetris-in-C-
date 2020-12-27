#include "TetrisShape.h"
#include "Board_2P.h"
#include "IGame.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>

class Game_2P : public IGame
{
public:
	using Position = sf::Vector2i;

public:
	Game_2P();
	void Run(bool&, uint16_t&);

private:
	void Proceed(Direction);
	void Proceed_2P(Direction);
	void Update(const sf::Time&);
	void Rotate();
	void Rotate_2P();
	void ScaleUp();
	void ScaleUp_2P();
	void ScaleDown();
	void ScaleDown_2P();
	void CreateShape();
	void CreateShape_2P();
	bool IsValidMovement(std::array<Position, 16>);
	bool IsOccupied(uint16_t, uint16_t);
	void ProcessEvents(bool&, uint16_t&);
	void Render();
	void FileWriter(std::string file);

private:
	std::unique_ptr<TetrisShape> m_tetrisShape_2P;
	std::unique_ptr<TetrisShape> m_preview_2P;
	std::unique_ptr<Player> m_player2;
	int m_ID_2P;
};

