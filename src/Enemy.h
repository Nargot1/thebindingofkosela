#pragma once
#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable {

public:
	Enemy(sf::FloatRect in_rect, int in_hp, int in_damage) 
		: 
		rect(in_rect),
		hp(in_hp),
		damage(in_damage)
	{}
	virtual void Update() {};
	virtual void TakeDamage(int damage) {
		hp -= damage;
		if (hp <= 0)
		{
			isAlive = false;
		}
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(sprite);
	}
	virtual sf::FloatRect GetRect() const
	{
		return rect;
	}
	bool IsAlive() const
	{
		return isAlive;
	}
protected:
	int hp;
	int damage;
	bool isAlive = true;
	sf::FloatRect rect;
	sf::Sprite sprite;
};