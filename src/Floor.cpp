#include "Floor.h"

Floor::Floor(std::vector<Room>& rooms)
	:
	rooms(rooms),
	activeRoom(Room())
{
	activeRoom = rooms.at(0);
}

void Floor::Draw(sf::RenderWindow& window)
{
	activeRoom.Draw(window);
}
