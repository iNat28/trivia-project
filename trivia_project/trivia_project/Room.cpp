#include "pch.h"
#include "Room.h"

RoomData::RoomData(unsigned int id, string name, vector<LoggedUser> players, unsigned int maxPlayers, unsigned int questionsCount, unsigned int timePerQuestion) : 
	id(id), name(name), players(players), maxPlayers(maxPlayers), questionsCount(questionsCount), timePerQuestion(timePerQuestion), roomStatus(RoomStatus::OPEN)
{
}

RoomData::RoomData() :
	id(0), name(), players(), maxPlayers(0), questionsCount(0), timePerQuestion(0), roomStatus(RoomStatus::OPEN)
{
}

void to_json(json& j, const RoomData& roomData)
{
	j[Keys::id] = roomData.id;
	j[Keys::roomName] = roomData.name;
	j[Keys::players] = roomData.players;
	j[Keys::maxPlayers] = roomData.maxPlayers;
	j[Keys::timePerQuestion] = roomData.timePerQuestion;
	j[Keys::questionsCount] = roomData.questionsCount;
	j[Keys::roomStatus] = roomData.roomStatus;
}

Room::Room(RoomData roomData) : 
	m_roomdata(roomData)
{
}

Room::Room()
{
}

void Room::addUser(LoggedUser user)
{
	if (this->m_roomdata.players.size() < this->m_roomdata.maxPlayers)
	{
		this->m_roomdata.players.push_back(user);
	}
	else
	{
		throw Exception("Room is full!");
	}
}

void Room::removeUser(LoggedUser user)
{
	for (auto it = this->m_roomdata.players.begin(); it != this->m_roomdata.players.end(); it++)
	{
		if (it->username == user.username)
		{
			this->m_roomdata.players.erase(it);
			return;
		}
	}
	throw Exception("User not found");
}

void Room::close()
{
	this->m_roomdata.roomStatus = RoomStatus::CLOSED;
}

vector<LoggedUser> Room::getAllUsers() const
{
	return this->m_roomdata.players;
}

RoomStatus Room::getRoomStatus() const
{
	return this->m_roomdata.roomStatus;
}

unsigned int Room::getId() const
{
	return this->m_roomdata.id;
}

void Room::setId(unsigned int id)
{
	this->m_roomdata.id = id;
}

void to_json(json& j, const Room& room)
{
	j[Keys::roomData] = room.m_roomdata;
}