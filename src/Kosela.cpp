#include "Kosela.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

void Kosela::update()
{
	up = false;
	down = false;
	left = false;
	right = false;

	pos += velocity;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		up = true;
	}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        left = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        down = true;
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		right = true;
	}

	if(up)
	{
		velocity.y -= acceleration;
		if(velocity.y < -maxSpeed)
		{
			velocity.y = -maxSpeed;
		}
	}

	if(down)
	{
		velocity.y += acceleration;
		if (velocity.y > maxSpeed)
		{
			velocity.y = maxSpeed;
		}
	}

	if(left)
	{
		velocity.x -= acceleration;
		if (velocity.x < -maxSpeed)
		{
			velocity.x = -maxSpeed;
		}
	}

    if (right)
    {
        velocity.x += acceleration;
		if (velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}
    }
)

void Kosela::draw(sf:RenderTarget& target)
{
	sf::Sprite sp;
	s.setPosition(pos.x, pos.y);
	target.draw(s);
}