#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Kosela.h"

class Room
{
public:
	Room() = default;
	Room(int width,int height, std::vector<sf::Vector2<int>> stones_in,std::vector<sf::Vector2<int>> doors_in, std::vector<int> doorsId);
	void Draw(sf::RenderWindow& window) const;
	void PlayerCollision(Kosela& kosela);
private:
	int width;
	int height;

	std::vector<sf::Vector2i> doors;
	std::vector<int> doorsID;
	std::vector<sf::Vector2i> stones;

	std::vector<Tile> tiles;

	class enum Direction
	{
		Up,
		Down,
		Left,
		Right
	};
};