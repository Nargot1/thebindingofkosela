#include "Kosela.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

Kosela::Kosela()
{
	rect = sf::FloatRect(500, 500, 64, 64);
}

void Kosela::update()
{
	bool keyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		rect.top -= acceleration;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rect.left -= acceleration;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		rect.top += acceleration;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rect.left += acceleration;
	}
}

void Kosela::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sp;
	sp.setPosition(rect.left, rect.top);
	sf::Texture texture;
	texture.loadFromFile("../Kosela.png");
	sp.setTexture(texture);
	target.draw(sp);
}
