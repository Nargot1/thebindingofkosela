#pragma once
#include <vector>
#include "Room.h"

class Floor
{
private:
	int nRooms = 0;
	std::vector<Room> rooms;

	Room* activeRoom;
public:
	Floor(std::vector<Room> rooms);
	void Draw(sf::RenderWindow& window);
	void ActiveRoomPlayerCollision(Kosela& kosela);
	Room* GetActiveRoom();
};
