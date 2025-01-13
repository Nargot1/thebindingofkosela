#pragma once
#include <SFML/Graphics.hpp>;
#include "Entity.h";

class Kosela : public sf::Drawable, public Entity
{
public:

	float maxSpeed = 3.0f;
	float acceleration = 0.3f;

	Kosela();

	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::IntRect rect;
};