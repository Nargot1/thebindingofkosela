#include "Dummy.h"
#include "Kosela.h"
#include <iostream>
#include <cmath>

Dummy::Dummy(sf::Vector2i pos)
	:
	Enemy(sf::FloatRect(500 + pos.x * 64, 250 + pos.y * 64, 52, 64), Health, Damage)
{
	sprite.setPosition(rect.left, rect.top);
	if (!texture.loadFromFile("../Dummy.png", sf::IntRect(0, 0, rect.width, rect.height))) {
		std::cerr << "Failed to load texture from ../Dummy.png" << std::endl;
	}
	sprite.setTexture(texture);
}

void Dummy::Update()
{
	sprite.setPosition(rect.left, rect.top);
}

void Dummy::FollowKosela(const Kosela& kosela)
{
	if (!isAlive) return;

	sf::FloatRect koselaRect = kosela.GetRect();

	sf::Vector2f direction;
	direction.x = (koselaRect.left + koselaRect.width / 2) - (rect.left + rect.width / 2);
	direction.y = (koselaRect.top + koselaRect.height / 2) - (rect.top + rect.height / 2);

	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	float minDistance = (rect.width + koselaRect.width) / 2.0f;

	if (distance < minDistance) {
		return;
	}

	if (distance > 0)
	{
		direction.x /= distance;
		direction.y /= distance;

		rect.left += direction.x * MoveSpeed;
		rect.top += direction.y * MoveSpeed;

		sprite.setPosition(rect.left, rect.top);
	}
}

void Dummy::DamageKosela(Kosela& kosela)
{
	if (!isAlive) return;

	sf::FloatRect koselaRect = kosela.GetRect();
	if (rect.intersects(koselaRect))
	{
		ResolveCollision(koselaRect);

		if (damageClock.getElapsedTime().asSeconds() >= DamageInterval)
		{
			kosela.TakeDamage(damage);
			damageClock.restart();
		}
	}
}


void Dummy::ResolveCollision(const sf::FloatRect& koselaRect)
{
	float overlapX = 0.0f;
	float overlapY = 0.0f;

	float dummyCenterX = rect.left + rect.width / 2.0f;
	float dummyCenterY = rect.top + rect.height / 2.0f;
	float koselaCenterX = koselaRect.left + koselaRect.width / 2.0f;
	float koselaCenterY = koselaRect.top + koselaRect.height / 2.0f;

	float dirX = dummyCenterX - koselaCenterX;
	float dirY = dummyCenterY - koselaCenterY;

	float overlapWidth = (rect.width + koselaRect.width) / 2.0f - std::abs(dirX);
	float overlapHeight = (rect.height + koselaRect.height) / 2.0f - std::abs(dirY);

	if (overlapWidth < overlapHeight)
	{
		overlapX = (dirX > 0) ? overlapWidth : -overlapWidth;
	}
	else
	{
		overlapY = (dirY > 0) ? overlapHeight : -overlapHeight;
	}

	rect.left += overlapX;
	rect.top += overlapY;
}
