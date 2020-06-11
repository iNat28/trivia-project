#include "pch.h"
#include "RoomManager.h"

RoomManager::RoomManager(IDatabase& database) : 
	m_database(database)
{
}

void RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
	Room newRoom(roomData);
	
	newRoom.getRoomData().name = user.username + "'s game";
	
	if (!this->m_rooms.empty())
	{
		//Gets the last id in the rooms
		newRoom.getRoomData().id = (--this->m_rooms.end())->first + 1;
	}
	else
	{
		newRoom.getRoomData().id = 1;
	}

	this->m_rooms[roomData.id] = newRoom;
}

void RoomManager::deleteRoom(unsigned int id)
{
	Room& room = getRoom(id);
	for (auto& user : room.getAllUsers())
	{
		this->m_database.addGameStats(user.username, GameStats(id, user.answerTime / room.getRoomData().id, ))
	}

	if (!this->m_rooms.erase(id))
	{
		throw Exception("Room ID not found");
	}
}

bool RoomManager::getRoomState(unsigned int id) const
{
	return this->_getRoom(id).getActivity();
}

Room& RoomManager::getRoom(unsigned int id)
{
	try
	{
		return this->m_rooms.at(id);
	}
	catch (const std::exception & e)
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
		rooms.push_back(room.second);
	}

	return rooms;
}

const Room& RoomManager::_getRoom(unsigned int id) const
{
	try
	{
		return this->m_rooms.at(id);
	}
	catch (const std::exception & e)
	{
		throw Exception("Room ID not found");
	}
}