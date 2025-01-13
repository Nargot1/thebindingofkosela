#include "Kosela.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

Kosela::Kosela()
	:
	rect({ 0,0,64,64 })
{
}

void Kosela::update()
{
	bool keyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= acceleration;
		if (velocity.y < -maxSpeed)
		{
			velocity.y = -maxSpeed;
		}
		keyPressed = true;
	}
	else
	{
		velocity.y += acceleration;
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= acceleration;
		if (velocity.x < -maxSpeed)
		{
			velocity.x = -maxSpeed;
		}
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += acceleration;
		if (velocity.y > maxSpeed)
		{
			velocity.y = maxSpeed;
		}
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += acceleration;
		if (velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}
		keyPressed = true;
	}
	if (keyPressed == false)
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	pos += velocity;
}

void Kosela::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sp;
	sp.setPosition(pos.x, pos.y);
	sf::Texture texture;
	texture.loadFromFile("../Kosela.png");
	sp.setTexture(texture);
	target.draw(sp);
}