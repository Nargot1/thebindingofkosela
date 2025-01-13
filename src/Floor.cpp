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
