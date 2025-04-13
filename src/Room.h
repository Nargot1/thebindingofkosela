#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Kosela.h"
#include <vector>
#include "Enemy.h"
#include "Dummy.h"
#include "Bomb.h"

class Room
{
public:
	Room() = default;
	Room(int width, int height, std::vector<sf::Vector2<int>> stones_in, std::vector<sf::Vector2<int>> doors_in, std::vector<int> doorsId, sf::Vector2i spawn, std::vector<Enemy*> enemies);
	void Draw(sf::RenderWindow& window) const;
	void Update(Kosela& kosela);
	int PlayerCollision(Kosela& kosela);
	sf::Vector2i GetSpawn() const
	{
		return spawn;
	}
	void AddBomb(sf::Vector2f position);
	std::vector<Enemy*>& GetEnemies();

private:
	bool CollisionCore(Tile& tile, Kosela& kosela);
	void ResolveDummyCollision(Dummy* dummy1, Dummy* dummy2);

	int width;
	int height;

	std::vector<sf::Vector2i> doors;
	std::vector<int> doorsID;
	std::vector<sf::Vector2i> stones;

	sf::Vector2i spawn;

	std::vector<Tile> tiles;
	std::vector<Enemy*> enemies;
	std::vector<Bomb> bombs;

	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};
};
