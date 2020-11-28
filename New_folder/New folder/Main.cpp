#include <SFML/Graphics.hpp>
#include "TetrisShape.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Test Window");
	sf::Texture texture;
	texture.loadFromFile("Blocks.png");

	TetrisShape Shape(texture, 3);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(Shape);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
			Shape.Rotate();
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			Shape.Move(Direction::Left);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			Shape.Move(Direction::Right);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Shape.Move(Direction::Down);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			Shape.ScaleUp();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			Shape.ScaleDown();

		window.display();
	}
	return 0;
}