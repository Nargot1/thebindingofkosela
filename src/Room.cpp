#include "Room.h"

Room::Room(int width_in, int height_in, std::vector<sf::Vector2<int>> stones, std::vector<sf::Vector2<int>> doors, std::vector<int> doorsId)
	:
	width(width_in+1),
	height(height_in+1),
	stones(stones),
	doors(doors),
	doorsID(doorsId)
{
	bool isStone = false;
	bool isDoors = false;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			for (int i = 0; i < stones.size(); i++)
			{
				if (stones.at(i) == sf::Vector2i(x, y))
				{
					tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Blocked, width, height));
					isStone = true;
					continue;
				}
			}
			if (isStone)
			{
				isStone = false;
				continue;
			}
			for (int i = 0; i < doors.size(); i++)
			{
				if (doors.at(i) == sf::Vector2i(x, y))
				{
					tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Doors, width, height));
					isDoors = true;
					continue;
				}
			}
			if (isDoors)
			{
				isDoors = false;
				continue;
			}
			if (y == 0 || y == height-1 || x == 0 || x == width-1)
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Wall, width, height));
				continue;
			}
			else
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Empty, width, height));
				continue;
			}
		}
	}
}

void Room::Draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles.at(i).Draw(window);
	}
}
