#include "Tile.h"

Tile::Tile(sf::Vector2f &pos, TileType type_in)
	:
	rect(pos,{size,size}),
	type(type_in),
	rectShape({ size,size })
{
	rectShape.setPosition(pos);
	rectShape.setFillColor(sf::Color::Yellow);
}

Tile::Tile(sf::Vector2f& pos, TileType type_in, WallDirection dir)
	:
	rect(pos, { size,size }),
	type(type_in),
	wallDirection(dir),
	rectShape({ size,size })
{
	rectShape.setPosition(pos);
}

void Tile::Draw(sf::RenderWindow& window) const
{
	window.draw(rectShape);
}
