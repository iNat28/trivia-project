#pragma once
#include "pch.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

struct RoomData 
{
	RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, unsigned int isActive);

	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
public:
	Room(unsigned int id, string name);
	Room();

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<LoggedUser> getAllUsers();
	int getActivity();
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};
