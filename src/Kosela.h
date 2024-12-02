#pragma once
#include <SFML/Graphics.hpp>;
#include "Entity.h";

class Kosela : public sf::Drawable, public Entity
{
public:
	bool up = false,
		down = false,
		left = false,
		right = false;

	float maxSpeed = 1.0,
		acceleration = 0.1;

	void update();
	void draw(sf::RenderTarget&) const;

	Kosela() {};
};