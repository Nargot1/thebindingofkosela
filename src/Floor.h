#pragma once
#include <vector>
#include "Room.h"
#include "Enemy.h"

class Floor
{
private:
	int ncurrRoom = 0;
	std::vector<Room*> rooms;

	Room* activeRoom;
public:
	Floor(std::vector<Room*> rooms);
	void Draw(sf::RenderWindow& window);
	void Update(Kosela& kosela)
	{
		activeRoom->Update(kosela);
	}
	bool ActiveRoomPlayerCollision(Kosela& kosela);
	Room* GetActiveRoom();
};
