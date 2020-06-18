#include "pch.h"
#include "Room.h"

Room::Room(RoomData roomData) :
	m_metadata(roomData)
{
}

Room::Room()
{
}

void Room::addUser(LoggedUser user)
{
	if (this->m_users.size() < this->m_metadata.maxPlayers)
	{
		this->m_users.push_back(user);
	}
}

void Room::removeUser(LoggedUser user)
{
	vector<LoggedUser>::iterator it;
	for (it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		if (it->username == user.username)
		{
			this->m_users.erase(it);
		}
	}
}

vector<LoggedUser> Room::getAllUsers() const
{
	return this->m_users;
}

int Room::getActivity() const
{
	return this->m_metadata.isActive;
}

const RoomData& Room::getRoomDataConst() const
{
	return this->m_metadata;
}

RoomData& Room::getRoomData()
{
	return this->m_metadata;
}

RoomData::RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, unsigned int isActive, unsigned int numQuestionsAsked) :
	id(id), name(name), maxPlayers(maxPlayers), timePerQuestion(timePerQuestion), isActive(isActive), numQuestionsAsked(numQuestionsAsked)
{
}

RoomData::RoomData() :
	id(0), maxPlayers(5), timePerQuestion(20), isActive(false), numQuestionsAsked(0)
{
}

void to_json(json& j, const Room& room)
{
	j[Keys::id] = room.getRoomDataConst().id;
	j[Keys::name] = room.getRoomDataConst().name;
	j[Keys::maxPlayers] = room.getRoomDataConst().maxPlayers;
	j[Keys::timePerQuestion] = room.getRoomDataConst().timePerQuestion;
	j[Keys::isActive] = room.getActivity();
	j[Keys::users] = room.getAllUsers();
	j[Keys::numQuestionsAsked] = room.getRoomDataConst().numQuestionsAsked;
}

void from_json(const json& j, Room& room)
{
	room = RoomData(
		j[Keys::id],
		j[Keys::name],
		j[Keys::maxPlayers],
		j[Keys::timePerQuestion],
		j[Keys::isActive],
		j[Keys::numQuestionsAsked]
	);
}