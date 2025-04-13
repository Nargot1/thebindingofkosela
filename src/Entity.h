#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
protected:
    
    sf::Sprite sprite;
public:
    enum class entityType {
        player,
    };

	sf::Vector2f velocity;

    sf::Sprite getSprite();
    void setSprite(sf::Sprite);
};