#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Room
{
public:
	Room(int width,int height, std::vector<sf::Vector2<int>> stones,std::vector<sf::Vector2<int>> doors, std::vector<int> doorsId);

private:
	int width;
	int height;

	Tile tiles[];
};