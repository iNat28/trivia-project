#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <iostream>
#include "LoggedUser.h"
using std::string;
using std::vector;

struct RoomData 
{
	int id;
	string name;
	int maxPlayers;
	int timePerQuestion;
	int isActive;
};

class Room
{
public:
	Room(int id, string name);
	Room() {}

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<LoggedUser> getAllUsers();
	int getActivity();

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};
