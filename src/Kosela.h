#pragma once
#include <SFML/Graphics.hpp>;
#include "Entity.h";

class Kosela : public sf::Drawable, public Entity
{
public:

	float maxSpeed = 1.0;
	float acceleration = 0.1;

	void update();
	void draw(sf::RenderTarget&) const;

	Kosela() {};
};