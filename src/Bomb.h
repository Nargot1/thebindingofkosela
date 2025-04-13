#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Bomb : public sf::Drawable {
public:
	Bomb(sf::Vector2f pos);
	void Update(std::vector<Enemy*>& enemies);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect GetRect() const;
	bool ShouldBeRemoved() const;
private:
	sf::Vector2i textureSize;
	sf::FloatRect rect;
	sf::Sprite sprite;
	sf::Texture texture;
	float timer = 0;
	float explosionTimer = 0;
	bool exploded = false;
	bool shouldBeRemoved = false;
};
