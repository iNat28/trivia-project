#pragma once
#include "pch.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

enum class RoomStatus
{
	OPEN,
	CLOSED,
	GAME_STARTED
};

struct RoomData
{
	RoomData(unsigned int id, string name, vector<LoggedUser> player, unsigned int maxPlayers, unsigned int questionsCount, unsigned int timePerQuestion);
	RoomData();

	unsigned int id;
	string name;
	vector<LoggedUser> players;
	unsigned int maxPlayers;
	unsigned int questionsCount;
	unsigned int timePerQuestion;
	RoomStatus roomStatus;
};

void to_json(json& j, const RoomData& roomData);

class Room
{
public:
	Room(RoomData roomData);
	Room();

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	void close();
	vector<LoggedUser> getAllUsers() const;
	RoomStatus getRoomStatus() const;
	unsigned int getId() const;
	void setId(unsigned int id);
	friend void to_json(json& j, const Room& room);
private:
	RoomData m_roomdata;
};
