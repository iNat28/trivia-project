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
		if (it->getUsername() == user.getUsername())
		{
			this->m_users.erase(it);
		}
	}
}

vector<LoggedUser> Room::getAllUsers()
{
	return this->m_users;
}

int Room::getActivity()
{
	return this->m_metadata.isActive;
}

RoomData::RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, unsigned int isActive) :
	id(id), name(name), maxPlayers(maxPlayers), timePerQuestion(timePerQuestion), isActive(isActive)
{
}