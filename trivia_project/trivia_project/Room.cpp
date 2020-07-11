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
	if (roomData.timePerQuestion > MAX_ANSWER_TIME)
	{
		Exception::ex << "Max answer time is " << MAX_ANSWER_TIME << '!';
		throw Exception();
	}
	else if (roomData.timePerQuestion < 1)
	{
		throw Exception("Minimum answer time is 1!");
	}
	else if (roomData.questionsCount > MAX_QUESTION_COUNT)
	{
		Exception::ex << "Max amount of questions is " << MAX_QUESTION_COUNT << '!';
		throw Exception();
	}
	else if (roomData.questionsCount < 1)
	{
		throw Exception("Minimum amount of questions is 1!");
	}
}

Room::Room()
{
}

void Room::addUser(LoggedUser& user)
{
	if (this->m_roomdata.players.size() >= this->m_roomdata.maxPlayers)
	{
		throw Exception("Room is full!");
	}
	if (this->m_roomdata.roomStatus == RoomStatus::CLOSED)
	{
		throw Exception("Room is closed!");
	}
	if (this->m_roomdata.roomStatus == RoomStatus::GAME_STARTED)
	{
		throw Exception("Room has started!");
	}
	this->m_roomdata.players.push_back(user);
}

void Room::removeUser(LoggedUser& user)
{
	for (auto it = this->m_roomdata.players.begin(); it != this->m_roomdata.players.end(); it++)
	{
		if (*it == user)
		{
			this->m_roomdata.players.erase(it);
			return;
		}
	}
	throw Exception("User not found");
}

unsigned int Room::getQuestionsCount() const
{
	return this->m_roomdata.questionsCount;
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

void Room::setRoomStatus(RoomStatus roomStatus)
{
	this->m_roomdata.roomStatus = roomStatus;
}

void to_json(json& j, const Room& room)
{
	j = room.m_roomdata;
}