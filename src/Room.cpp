#include "Room.h"

Room::Room(int width_in, int height_in, std::vector<sf::Vector2<int>> stones, std::vector<sf::Vector2<int>> doors, std::vector<int> doorsId, sf::Vector2i spawn, std::vector<Enemy*> enemies)
	:
	width(width_in + 1),
	height(height_in + 1),
	stones(stones),
	doors(doors),
	doorsID(doorsId),
	spawn(spawn),
	enemies(enemies)
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
					if (y == 0)
					{
						tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Doors, width, height, Tile::WallDirection::Bottom));

					}
					else if (y == height - 1)
					{
						tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Doors, width, height, Tile::WallDirection::Top));

					}
					else if (x == 0)
					{
						tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Doors, width, height, Tile::WallDirection::Right));

					}
					else if (x == width - 1)
					{
						tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Doors, width, height, Tile::WallDirection::Left));

					}
					isDoors = true;
					continue;
				}
			}
			if (isDoors)
			{
				isDoors = false;
				continue;
			}
			if (y == 0)
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Wall, width, height, Tile::WallDirection::Bottom));
				continue;
			}
			else if (y == height - 1)
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Wall, width, height, Tile::WallDirection::Top));
				continue;
			}
			else if (x == 0)
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Wall, width, height, Tile::WallDirection::Right));
				continue;
			}
			else if (x == width - 1)
			{
				tiles.push_back(Tile(sf::Vector2i(x, y), Tile::TileType::Wall, width, height, Tile::WallDirection::Left));
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

	for (const auto& bomb : bombs)
	{
		bomb.draw(window, sf::RenderStates::Default);
	}

	for (auto e : enemies)
	{
		e->draw(window, sf::RenderStates::Default);
	}
}

void Room::Update(Kosela& kosela)
{
	for (auto e : enemies)
	{
		if (Dummy* dummy = dynamic_cast<Dummy*>(e))
		{
			dummy->FollowKosela(kosela);
			dummy->DamageKosela(kosela);
			dummy->Update();
		}
	}

	for (size_t i = 0; i < enemies.size(); ++i)
	{
		Dummy* dummy1 = dynamic_cast<Dummy*>(enemies[i]);
		if (!dummy1) continue;

		for (size_t j = i + 1; j < enemies.size(); ++j)
		{
			Dummy* dummy2 = dynamic_cast<Dummy*>(enemies[j]);
			if (!dummy2) continue;

			sf::FloatRect rect1 = dummy1->GetRect();
			sf::FloatRect rect2 = dummy2->GetRect();

			if (rect1.intersects(rect2))
			{
				ResolveDummyCollision(dummy1, dummy2);
			}
		}
	}

	for (auto it = bombs.begin(); it != bombs.end();)
	{
		it->Update(enemies);

		sf::FloatRect bombRect = it->GetRect();
		if (bombRect.intersects(kosela.GetRect()))
		{
			//kosela.TakeDamage(10);
		}

		if (it->ShouldBeRemoved())
		{
			it = bombs.erase(it);
		}
		else
		{
			++it;
		}
	}
}



void Room::AddBomb(sf::Vector2f position)
{
	bombs.emplace_back(position);
}

void Room::ResolveDummyCollision(Dummy* dummy1, Dummy* dummy2)
{
	dummy1->ResolveCollision(dummy2->GetRect());
	dummy2->ResolveCollision(dummy1->GetRect());
}

std::vector<Enemy*>& Room::GetEnemies()
{
	return enemies;
}

int Room::PlayerCollision(Kosela& kosela)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		int ndoors = 0;
		Tile& tile = tiles.at(i);
		switch (tile.GetType()) {
		case Tile::TileType::Blocked:
		case Tile::TileType::Wall:
			CollisionCore(tile, kosela);
			break;
		case Tile::TileType::Doors:
			if (CollisionCore(tile, kosela))
			{
				bool isAlive = false;
				for (auto e:enemies)
				{
					if (e->IsAlive())
					{
						return -2;
					}
				}
				return doorsID[ndoors++];
			}
			break;
		}
	}
	return -2;
}

bool Room::CollisionCore(Tile& tile, Kosela& kosela)
{

	sf::FloatRect tileRect = tile.GetRect();
	sf::FloatRect playerRect = kosela.rect;

	if (tile.GetRect().intersects(playerRect))
	{
		float smallest = playerRect.left + playerRect.width - tileRect.left;
		Tile::WallDirection dir = tile.GetWallDir() == Tile::WallDirection::None ? Tile::WallDirection::Left : tile.GetWallDir();
		if (tile.GetWallDir() == Tile::WallDirection::None)
		{
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
	return false;
}
