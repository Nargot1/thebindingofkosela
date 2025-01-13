#include "Tile.h"

Tile::Tile(sf::Vector2i &pos, TileType type_in,int width_in,int height_in)
	:
	rect(sf::Vector2f(pos.x*size,pos.y*size), {size,size}),
	type(type_in),
	rectShape({ size,size })
{
	//int width = 960 - (width_in * size)/2;
	//int height = 540 - (height_in * size)/2;
	rectShape.setPosition(rect.getPosition() + sf::Vector2f(500,300));
	if (type == TileType::Wall)
		rectShape.setFillColor(sf::Color::Green);
	else if(type == TileType::Blocked)
		rectShape.setFillColor(sf::Color::Blue);
	else if(type == TileType::Doors)
		rectShape.setFillColor(sf::Color::Red);
	else
		rectShape.setFillColor(sf::Color::Yellow);
	
}

Tile::Tile(sf::Vector2i& pos, TileType type_in, int width, int height, WallDirection dir)
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
