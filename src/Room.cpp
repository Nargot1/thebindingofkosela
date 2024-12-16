#include "Room.h"

Room::Room(int width, int height, std::vector<sf::Vector2<int>> stones, std::vector<sf::Vector2<int>> doors, std::vector<int> doorsId)
	:
	width(width),
	height(height),
	stones(stones),
	doors(doors),
	doorsID(doorsId)
{
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < height; x++)
		{
			for (int i = 0; i < stones.size(); i++)
			{
				if (stones.at(i) == sf::Vector2i(x, y))
				{
					tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Blocked));
					continue;
				}
			}
			for (int i = 0; i < doors.size(); i++)
			{
				if (doors.at(i) == sf::Vector2i(x, y))
				{
					tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Doors));
					continue;
				}
			}
			if (y == 0 || y == height-1 || x == 0 || x == width-1)
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Wall));
				continue;
			}
			else
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Empty));
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
