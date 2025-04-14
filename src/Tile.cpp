#include "Tile.h"

Tile::Tile(sf::Vector2i &pos, TileType type_in,int width_in,int height_in)
	:
	rect(sf::Vector2f(pos.x*size + 500,pos.y*size + 250), {size,size}),
	type(type_in),
	rectShape({ size,size })
{
	//int width = 960 - (width_in * size)/2;
	//int height = 540 - (height_in * size)/2;
	rectShape.setPosition(rect.getPosition());
	if (type == TileType::Wall)
		rectShape.setFillColor(sf::Color(50,100,255,255));
	else if(type == TileType::Blocked)
		rectShape.setFillColor(sf::Color(100,100,125,255));
	else if(type == TileType::Doors)
		rectShape.setFillColor(sf::Color(200,125,100,255));
	else
		rectShape.setFillColor(sf::Color(255,255,233,255));
	
}

Tile::Tile(sf::Vector2i& pos, TileType type_in, int width, int height, WallDirection dir)
	:
	rect(sf::Vector2f(pos.x* size + 500, pos.y* size + 250), { size,size }),
	type(type_in),
	rectShape({ size,size }),
	wallDirection(dir)
{
	//int width = 960 - (width_in * size)/2;
	//int height = 540 - (height_in * size)/2;
	rectShape.setPosition(rect.getPosition());
	if (type == TileType::Wall)
		rectShape.setFillColor(sf::Color(50, 100, 255, 255));
	else if (type == TileType::Blocked)
		rectShape.setFillColor(sf::Color(100, 100, 125, 255));
	else if (type == TileType::Doors)
		rectShape.setFillColor(sf::Color(200, 125, 100, 255));
	else
		rectShape.setFillColor(sf::Color(255, 255, 233, 255));

}

void Tile::Draw(sf::RenderWindow& window) const
{
	window.draw(rectShape);
}

Tile::WallDirection Tile::GetWallDir() const
{
	return wallDirection;
}

Tile::TileType Tile::GetType() const
{
	return type;
}

sf::FloatRect Tile::GetRect() const
{
	return rect;
}
