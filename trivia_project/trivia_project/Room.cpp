#include "Room.h"

Room::Room(int id, string name)
{
	this->m_metadata.id = id;
	this->m_metadata.name = name;
	this->m_metadata.maxPlayers = 5;
	this->m_metadata.timePerQuestion = 20;
	this->m_metadata.isActive = 0;
}

void Room::addUser(LoggedUser user)
{
	if (this->m_users.size < 5)
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


