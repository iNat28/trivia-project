#include "pch.h"
#include "Room.h"

Room::Room(unsigned int id, string name) :
	m_metadata(RoomData{id, name, 5, 20, 0})
{
}

Room::Room() :
	Room(0, "")
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
		if (it->m_username == user.m_username)
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

RoomData Room::getRoomData() const
{
	return this->m_metadata;
}

RoomData::RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, unsigned int isActive) :
	id(id), name(name), maxPlayers(maxPlayers), timePerQuestion(timePerQuestion), isActive(isActive)
{
}

void to_json(json& j, const Room& room)
{
	j[Keys::id] = room.getRoomData().id;
	j[Keys::name] = room.getRoomData().name;
	j[Keys::maxPlayers] = room.getRoomData().maxPlayers;
	j[Keys::timePerQuestion] = room.getRoomData().timePerQuestion;
	j[Keys::isActive] = room.getActivity();
	j[Keys::users] = room.getAllUsers();
}

void from_json(const json& j, Room& room)
{
	room = Room(
		j[Keys::id],
		j[Keys::name]
	);
}