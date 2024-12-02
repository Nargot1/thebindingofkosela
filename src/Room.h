#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Room
{
public:
	Room();

private:
	int width;
	int height;

	Tile tiles[];
};