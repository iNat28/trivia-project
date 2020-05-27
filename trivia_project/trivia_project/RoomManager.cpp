#include "pch.h"
#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user)
{
	map<int, Room>::iterator it;
	int id = 1;
	string name = user.getUsername() + "'s game";
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
//lol
bool RoomManager::getRoomState(int id)
{
	return this->m_rooms[id].getActivity();
}

vector<Room> RoomManager::getRooms()
{
	vector<Room> rooms;
	map<int, Room>::iterator it;
	for (it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		rooms.push_back(it->second);
	}
	return rooms;
}
