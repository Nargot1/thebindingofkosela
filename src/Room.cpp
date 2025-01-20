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

int Room::PlayerCollision(Kosela& kosela)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		Tile& tile = tiles.at(i);
		switch (tile.GetType()) {
			case Tile::TileType::Blocked:
			case Tile::TileType::Wall:
				CollisionCore(tile,kosela);
				break;
			case Tile::TileType::Doors:
				if (CollisionCore(tile, kosela))
				{
					return 1;
				}
				break;
		}
	}
	return -1;
}

bool Room::CollisionCore(Tile& tile, Kosela& kosela)
{

	sf::FloatRect tileRect = tile.GetRect();
	sf::FloatRect playerRect = kosela.rect;

	if (tile.GetRect().intersects(playerRect))
	{
		float smallest = playerRect.left + playerRect.width - tileRect.left;
		Tile::WallDirection dir = Tile::WallDirection::Left;
		if (tileRect.left + tileRect.width - kosela.rect.left < smallest)
		{
			smallest = (tileRect.left + tileRect.width - kosela.rect.left);
			dir = Tile::WallDirection::Right;
		}
		if (tileRect.top + tileRect.height - kosela.rect.top < smallest)
		{
			smallest = ((tileRect.top + tileRect.height) - playerRect.top);
			dir = Tile::WallDirection::Bottom;
		}
		if (kosela.rect.top + kosela.rect.height - tileRect.top < smallest)
		{
			smallest = tileRect.top - (playerRect.top + playerRect.height);
			dir = Tile::WallDirection::Top;
		}
		switch (dir)
		{
		case Tile::WallDirection::Left:
			kosela.rect = sf::FloatRect(kosela.rect.left - (kosela.rect.left + kosela.rect.width - tileRect.left), kosela.rect.top, kosela.rect.width, kosela.rect.height);
			break;
		case Tile::WallDirection::Right:
			kosela.rect = sf::FloatRect(kosela.rect.left + (tileRect.left + tileRect.width - kosela.rect.left), kosela.rect.top, kosela.rect.width, kosela.rect.height);
			break;
		case Tile::WallDirection::Top:
			kosela.rect = sf::FloatRect(kosela.rect.left, kosela.rect.top - (kosela.rect.top + kosela.rect.height - tileRect.top), kosela.rect.width, kosela.rect.height);
			break;
		case Tile::WallDirection::Bottom:
			kosela.rect = sf::FloatRect(kosela.rect.left, kosela.rect.top + (tileRect.top + tileRect.height - kosela.rect.top), kosela.rect.width, kosela.rect.height);
			break;
		default:
			break;
		}
		return true;
	}
}
