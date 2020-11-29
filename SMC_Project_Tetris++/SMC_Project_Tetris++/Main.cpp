#include <SFML/Graphics.hpp>
#include "TetrisShape.h"
#include "Menu.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Test Window");
	sf::Texture texture;
	if (!texture.loadFromFile("Blocks.png"))
		std::cout << "Can't load the texture from the file !" << std::endl;

	TetrisShape shape(texture, 3);

	/*Menu menu(window.getSize().x, window.getSize().y);*/

	while (window.isOpen())
	{
		sf::Event event;
		window.clear();
		window.draw(shape);
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
				/*case(sf::Keyboard::Return):
					menu.draw(window);
					break;*/
				default:
					break;
				}
			}
		}

		window.display();
	}

	return 0;
}