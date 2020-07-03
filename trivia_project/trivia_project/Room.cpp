#include "pch.h"
#include "Room.h"

RoomState::RoomState(vector<LoggedUser> players, unsigned int maxPlayers, unsigned int questionsCount, unsigned int timePerQuestion) :
	players(players), maxPlayers(maxPlayers), questionsCount(questionsCount), timePerQuestion(timePerQuestion), didGameStart(false)
{
}

RoomState::RoomState() :
	players(), maxPlayers(0), questionsCount(0), timePerQuestion(0), didGameStart(false)
{
}

void to_json(json& j, const RoomState& roomState)
{
	j[Keys::players] = roomState.players;
	j[Keys::maxPlayers] = roomState.maxPlayers;
	j[Keys::timePerQuestion] = roomState.timePerQuestion;
	j[Keys::questionsCount] = roomState.questionsCount;
	j[Keys::didGameStart] = roomState.didGameStart;
}

RoomData::RoomData(unsigned int id, string name) :
	id(id), name(name), isClosed(false)
{
}

RoomData::RoomData() :
	id(0), name(), isClosed(false)
{
}

void to_json(json& j, const RoomData& roomData)
{
	j[Keys::id] = roomData.id;
	j[Keys::roomName] = roomData.name;
}

Room::Room(RoomData roomData, RoomState roomState) :
	m_roomdata(roomData), m_roomstate(roomState)
{
}

Room::Room()
{
}

void Room::addUser(LoggedUser user)
{
	if (this->m_roomstate.players.size() < this->m_roomstate.maxPlayers)
	{
		this->m_roomstate.players.push_back(user);
	}
	else
	{
		throw Exception("Room is full!");
	}
}

void Room::removeUser(LoggedUser user)
{
	for (auto it = this->m_roomstate.players.begin(); it != this->m_roomstate.players.end(); it++)
	{
		if (it->username == user.username)
		{
			this->m_roomstate.players.erase(it);
			return;
		}
	}
	throw Exception("User not found");
}

void Room::close()
{
	this->m_roomdata.isClosed = true;
}

vector<LoggedUser> Room::getAllUsers() const
{
	return this->m_roomstate.players;
}

RoomState Room::getRoomState() const
{
	return this->m_roomstate;
}

bool Room::didGameStart() const
{
	return this->m_roomstate.didGameStart;
}

bool Room::isClosed() const
{
	return this->m_roomdata.isClosed;
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
	j[Keys::roomState] = room.m_roomstate;
}