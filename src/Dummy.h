#pragma once
#include "Enemy.h"
#include "Kosela.h"

class Dummy : public Enemy
{
public:
	Dummy(sf::Vector2i pos);
	void Update() override;
	void FollowKosela(const Kosela& kosela);
	void DamageKosela(Kosela& kosela);
	void ResolveCollision(const sf::FloatRect& koselaRect);

public:
	static constexpr int Width = 52;
	static constexpr int Height = 64;
	static constexpr int Health = 100;
	static constexpr int Damage = 10;
	static constexpr float MoveSpeed = 2.0f;
	static constexpr float DamageInterval = 1.0f;

private:
	sf::Texture texture;
	sf::Clock damageClock;
};
