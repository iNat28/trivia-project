#include "pch.h"
#include "RoomManager.h"

RoomManager::RoomManager(IDatabase& database) : 
	m_database(database)
{
}

void RoomManager::createRoom(Room& room)
{
	room.setId(this->m_database.getHighestRoomId());

	this->m_rooms[room.getId()] = room;
}

void RoomManager::closeRoom(Room& room)
{
	room.setRoomStatus(RoomStatus::CLOSED);

	if (room.getAllUsers().empty())
	{
		if (!this->m_rooms.erase(room.getId()))
		{
			throw Exception("Room ID not found");
		}
	}
}

Room& RoomManager::getRoom(unsigned int id)
{
	try
	{
		return this->m_rooms.at(id);
	}
	catch (const std::exception&)
	{
		throw Exception("Room ID not found");
	}
}

vector<LoggedUser> RoomManager::getUsersInRoom(unsigned int id) const
{
	return this->_getRoom(id).getAllUsers();
}

vector<Room> RoomManager::getRooms() const
{
	vector<Room> rooms;

	for (const auto& room : this->m_rooms)
	{
		if (room.second.getRoomStatus() != RoomStatus::CLOSED)
		{
			rooms.push_back(room.second);
		}
	}

	return rooms;
}

const Room& RoomManager::_getRoom(unsigned int id) const
{
	try
	{
		return this->m_rooms.at(id);
	}
	catch (const std::exception&)
	{
		throw Exception("Room ID not found");
	}
}
