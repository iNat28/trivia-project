#include "pch.h"
#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user)
{
	map<int, Room>::iterator it;
	int id = 1;
	string name = user.m_username + "'s game";
	for (it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		id = it->first;
	}
	Room newRoom(id, name);
	this->m_rooms[id] = newRoom;
}

void RoomManager::deleteRoom(int id)
{
	map<int, Room>::iterator it;
	for (it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		if (it->first == id)
			this->m_rooms.erase(it);
	}
}

bool RoomManager::getRoomState(int id) const
{
	return this->m_rooms.at(id).getActivity();
}

vector<Room> RoomManager::getRooms() const
{
	vector<Room> rooms;

	for (const auto& room : this->m_rooms)
	{
		rooms.push_back(room.second);
	}

	return rooms;
}
