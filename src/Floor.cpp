#include "Floor.h"

Floor::Floor(std::vector<Room>& rooms)
	:
	rooms(rooms),
	activeRoom(rooms.at(0))
{
}