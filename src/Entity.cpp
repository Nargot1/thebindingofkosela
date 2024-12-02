include "Entity.h"
#include "SFML/Graphics.hpp"

sf::FloatRect Entity::getRect()
{
	return rect;
}

sf::Sprite Entity::getSprite()
{
    return sprite;
}

void Entity::setRect(sf::FloatRect r)
{
	rect = r;
}

void Entity::setSprite(sf::Sprite s)
{
    sprite = s;
}