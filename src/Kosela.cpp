#include "Kosela.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Room.h"
#include <string>

Kosela::Kosela(sf::Vector2i spawnPoint)
{
	rect = sf::FloatRect(500 + spawnPoint.x * 64, 250 + spawnPoint.y * 64, 52, 64);
	bombClock.restart();
}

void Kosela::SetPosition(sf::Vector2i pos)
{
	rect.left = 500 + pos.x * 64;
	rect.top = 250 + pos.y * 64;
}

void Kosela::TakeDamage(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		isAlive = false;
		hp = 0;
	}
}

bool Kosela::IsAlive() const
{
	return isAlive;
}

sf::FloatRect Kosela::GetRect() const
{
	return rect;
}

void Kosela::update(Room* currentRoom)
{
	if (!isAlive) return;

	bool keyPressed = false;
	sf::Vector2f movement(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.x -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.y -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.x += 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.y += 1;
	}

	if (movement != sf::Vector2f{ 0,0 })
	{
		float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
		rect.top += (movement.x / length) * acceleration;
		rect.left += (movement.y / length) * acceleration;
	}

	float elapsedTime = bombClock.getElapsedTime().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsedTime >= bombCooldown)
	{
		sf::Vector2f bombPosition(rect.left, rect.top);
		currentRoom->AddBomb(bombPosition);

		bombClock.restart();
		bombCooldown = 1.5f;
	}
}

void Kosela::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sp;
	sp.setPosition(rect.left, rect.top);
	sf::Texture texture;
	texture.loadFromFile("../Kosela.png", sf::IntRect(0, 0, rect.width, rect.height));
	sp.setTexture(texture);
	target.draw(sp);

	if (isAlive)
	{
		sf::RectangleShape hpBackground;
		hpBackground.setSize(sf::Vector2f(60.0f, 8.0f));
		hpBackground.setFillColor(sf::Color(100, 100, 100));
		hpBackground.setPosition(rect.left - 4, rect.top - 15);
		target.draw(hpBackground);

		sf::RectangleShape hpBar;
		float hpRatio = static_cast<float>(hp) / 100.0f;
		hpBar.setSize(sf::Vector2f(60.0f * hpRatio, 8.0f));
		hpBar.setFillColor(sf::Color(255, 0, 0));
		hpBar.setPosition(rect.left - 4, rect.top - 15);
		target.draw(hpBar);
	}
}

