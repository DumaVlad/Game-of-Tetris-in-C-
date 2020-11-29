#include <SFML/Graphics.hpp>
#include "TetrisShape.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Test Window");
	sf::Texture texture;
	if (!texture.loadFromFile("Blocks.png"))
		std::cout << "Can't load the texture from the file !" << std::endl;
	
	TetrisShape shape(texture, 6);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
	
		window.clear();
		window.draw(shape); 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			shape.Rotate(); 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shape.Move(Direction::Left);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shape.Move(Direction::Right);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shape.Move(Direction::Down);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			shape.ScaleUp();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			//shape.ScaleDown(); TO BE implemented
		}

		window.display();
	}
	
	return 0;
}        