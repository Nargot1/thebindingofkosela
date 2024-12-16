#include "Tile.h"

Tile::Tile(sf::Vector2i &pos, TileType type_in)
	:
	rect(sf::Vector2f(pos.x*size,pos.y*size), {size,size}),
	type(type_in),
	rectShape({ size,size })
{
	rectShape.setPosition(sf::Vector2f(pos.x * size, pos.y * size));
	if (type == TileType::Wall)
		rectShape.setFillColor(sf::Color::Green);
	else
		rectShape.setFillColor(sf::Color::Yellow);
	
}

Tile::Tile(sf::Vector2i& pos, TileType type_in, WallDirection dir)
	:
	rect(sf::Vector2f(pos.x* size, pos.y* size), { size,size }),
	type(type_in),
	wallDirection(dir),
	rectShape({ size,size })
{
	rectShape.setPosition(sf::Vector2f(pos.x*size,pos.y*size));
}

void Tile::Draw(sf::RenderWindow& window) const
{
	window.draw(rectShape);
}
