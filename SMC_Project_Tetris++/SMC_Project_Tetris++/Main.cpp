#include <SFML/Graphics.hpp>
#include <iostream>

#include "TetrisShape.h"
#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

	sf::Texture textureMenu;
	sf::Texture textureShape;
	sf::Sprite spriteMenu;
	bool menuOrGame = 1; // 1 for Menu, 0 for Game

	if (!textureMenu.loadFromFile("tetris600x600.jpg"))
	{
		std::cout << "Can't load the texture from the file !" << std::endl;
	}

	if (!textureShape.loadFromFile("Blocks.png"))
	{
		std::cout << "Can't load the texture from the file !" << std::endl;
	}

	textureMenu.setSmooth(true);
	spriteMenu.setTexture(textureMenu);
	spriteMenu.setOrigin(0, 0);

	TetrisShape shape(textureShape, 6);
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		if (menuOrGame)
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case::sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed!" << std::endl;
							menuOrGame = 0;
							break;
						case 1:
							std::cout << "Options button has been pressed!" << std::endl;
							break;
						case 2:
							window.close();
							break;
						}
						break;
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
		else
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
					case(sf::Keyboard::Escape):
						window.close();
						break;
					case(sf::Keyboard::Up):
						shape.Rotate();
						break;
					case(sf::Keyboard::Down):
						shape.Move(Direction::Down);
						break;
					case(sf::Keyboard::Left):
						shape.Move(Direction::Left);
						break;
					case(sf::Keyboard::Right):
						shape.Move(Direction::Right);
						break;
					case(sf::Keyboard::A):
						shape.ScaleUp();
						break;
					case(sf::Keyboard::Z):
						shape.ScaleDown();
						break;
					case(sf::Keyboard::Tilde):
						menuOrGame = 1;
						break;
					default:
						break;
					}
				}
			}

		window.clear();
		if (menuOrGame)
		{
			window.draw(spriteMenu);
			menu.draw(window);
		}
		else
		{
			window.draw(shape);
		}
		window.display();
	}

	return 0;
}