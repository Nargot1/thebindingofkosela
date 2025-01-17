#include "Kosela.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

Kosela::Kosela()
{
	rect = sf::FloatRect(800, 500, 52, 64);
}

void Kosela::update()
{
	bool keyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		rect.top -= acceleration;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rect.left -= acceleration;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		rect.top += acceleration;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rect.left += acceleration;
	}
}

void Kosela::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sp;
	sp.setPosition(rect.left, rect.top);
	sf::Texture texture;
	texture.loadFromFile("../Kosela.png",sf::IntRect(0,0,rect.width,rect.height));
	sp.setTexture(texture);
	target.draw(sp);
}
