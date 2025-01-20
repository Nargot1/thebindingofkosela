#include "Floor.h"

Floor::Floor(std::vector<Room> rooms_in)
	:
	rooms(rooms_in)
{
	activeRoom = &rooms.at(0);
}

void Floor::Draw(sf::RenderWindow& window)
{
	activeRoom->Draw(window);
}

void Floor::ActiveRoomPlayerCollision(Kosela& kosela)
{
	if (activeRoom->PlayerCollision(kosela))
	{
		activeRoom = &rooms.at(1);
	}
}

Room* Floor::GetActiveRoom()
{
	return activeRoom;
}
