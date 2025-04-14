#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Room;

class Kosela : public sf::Drawable, protected Entity
{
public:
	sf::FloatRect rect;
	float acceleration = 5.0f;
	int hp = 100;
	bool isAlive = true;

	Kosela(sf::Vector2i spawnPoint);

	void SetPosition(sf::Vector2i pos);
	void TakeDamage(int damage);
	bool IsAlive() const;
	sf::FloatRect GetRect() const;
	void update(Room* currentRoom);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float bombCooldown = 1.0f;
	sf::Clock bombClock;
};
