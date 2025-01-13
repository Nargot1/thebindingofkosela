#pragma once
#include <SFML/Graphics.hpp>;
#include "Entity.h";

class Kosela : public sf::Drawable, protected Entity
{
public:
	sf::FloatRect rect;
	float maxSpeed = 3.0f;
	float acceleration = 5.0f;

	Kosela();

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};