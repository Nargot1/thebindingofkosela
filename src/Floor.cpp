#include "Floor.h"
#include "Dummy.h"

Floor::Floor(std::vector<Room*> rooms_in)
	:
	rooms(rooms_in)
{
	activeRoom = rooms.at(0);
	ncurrRoom = 0;
}

void Floor::Draw(sf::RenderWindow& window)
{
	activeRoom->Draw(window);
}

bool Floor::ActiveRoomPlayerCollision(Kosela& kosela)
{
	int roomId = activeRoom->PlayerCollision(kosela);
	if (roomId != -2)
	{
		if (roomId == -1)
		{
			return true;
		}
		else
		{
			activeRoom = rooms.at(roomId);
			kosela.SetPosition(activeRoom->GetSpawn());
		}
	}
	return false;
}

Room* Floor::GetActiveRoom()
{
	return activeRoom;
}
