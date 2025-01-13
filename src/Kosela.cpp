#include "Kosela.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

void Kosela::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= acceleration;
		if (velocity.y < -maxSpeed)
		{
			velocity.y = -maxSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= acceleration;
		if (velocity.x < -maxSpeed)
		{
			velocity.x = -maxSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += acceleration;
		if (velocity.y > maxSpeed)
		{
			velocity.y = maxSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += acceleration;
		if (velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}
	}

	pos += velocity;
}

void Kosela::draw(sf:RenderTarget& target)
{
	sf::Sprite sp;
	s.setPosition(pos.x, pos.y);
	target.draw(s);
}