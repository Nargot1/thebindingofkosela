#include "Bomb.h"
#include "Kosela.h"
#include <iostream>

Bomb::Bomb(sf::Vector2f pos)
{
	textureSize = sf::Vector2i(50, 30);
	sprite.setTextureRect(sf::IntRect(sf::Vector2i{ 0,0 }, textureSize));
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	rect = sprite.getGlobalBounds();
	rect.width *= 2;
	rect.height *= 2;
}

void Bomb::Update(std::vector<Enemy*>& enemies)
{
	if (!exploded)
	{
		timer += 0.1f;
		sprite.setTextureRect(sf::IntRect({ (int)timer * textureSize.x,0 }, textureSize));
		if (timer >= 8.0f)
		{
			for (auto i = enemies.begin(); i != enemies.end(); i++)
			{
				if ((*i)->GetRect().intersects(rect))
				{
					(*i)->TakeDamage(50);
				}
			}
			timer = 0;
			exploded = true;

			sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

			explosionTimer = 0.0f;
		}
	}
	else
	{
		explosionTimer += 0.1f;

		if (explosionTimer >= 2.0f)
		{
			shouldBeRemoved = true;
		}
	}
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

sf::FloatRect Bomb::GetRect() const
{
	return rect;
}

bool Bomb::ShouldBeRemoved() const
{
	return shouldBeRemoved;
}
