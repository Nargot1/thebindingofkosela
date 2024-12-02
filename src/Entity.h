#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
private:
    sf::FloatRect rect;
    sf::Sprite sprite;
    
public:
    enum class entityType {
        player,
    };

	sf::Vector2f velocity;
	sf::Vector2f pos;

    sf::FloatRect getRect();
    sf::Sprite getSprite();
    void setRect(sf::FloatRect);
    void setSprite(sf::Sprite);
};