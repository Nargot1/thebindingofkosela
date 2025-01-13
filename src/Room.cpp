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

void Room::PlayerCollision(Kosela& kosela)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		Tile& tile = tiles.at(i);
		sf::FloatRect tileRect = tile.GetRect();
		sf::FloatRect playerRect = kosela.rect;
		switch (tile.GetType()) {
			case Tile::TileType::Blocked:
				if (tile.GetRect().intersects(playerRect))
				{
					float smallest = tile.GetRect().left - (playerRect.left + playerRect.width);
					Tile::WallDirection dir = Tile::WallDirection::Left;
					if (((tileRect.left + tileRect.width) - playerRect.left) < smallest)
					{
						smallest = ((tileRect.left + tileRect.width) - playerRect.left);
						dir = Tile::WallDirection::Right;
					}
					if (((tileRect.top + tileRect.height) - playerRect.top) < smallest)
					{
						smallest = ((tileRect.top + tileRect.height) - playerRect.top);
						dir = Tile::WallDirection::Bottom;
					}
					if (tileRect.top - (playerRect.top + playerRect.height) < smallest)
					{
						smallest = tileRect.top - (playerRect.top + playerRect.height);
						dir = Tile::WallDirection::Top;
					}
					switch (dir)
					{
					case Tile::WallDirection::Left:
						 kosela.rect = sf::FloatRect(kosela.rect.left, kosela.rect.top, kosela.rect.width, kosela.rect.height);
						break;
					case Tile::WallDirection::Right:
						break;
					case Tile::WallDirection::Top:
						break;
					case Tile::WallDirection::Bottom:
						break;
					default:
						break;
					}
				}
				break;
		}
	}
}
