#pragma once
#include "pch.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

struct RoomData 
{
	RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, unsigned int isActive);
	RoomData();

	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
public:
	Room(RoomData roomData);
	Room();

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<LoggedUser> getAllUsers() const;
	int getActivity() const;
	RoomData& getRoomData();
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};

void to_json(json& j, const Room& room);
void from_json(const json& j, Room& room);