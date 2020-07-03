#pragma once
#include "pch.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

struct RoomState
{
	RoomState(vector<LoggedUser> players, unsigned int maxPlayers, unsigned int questionsCount, unsigned int timePerQuestion);
	RoomState();

	vector<LoggedUser> players;
	unsigned int maxPlayers;
	unsigned int questionsCount;
	unsigned int timePerQuestion;
	bool didGameStart;
};

void to_json(json& j, const RoomState& roomState);

struct RoomData
{
	RoomData(unsigned int id, string name);
	RoomData();

	unsigned int id;
	string name;
	bool isClosed;
};

void to_json(json& j, const RoomData& roomData);

class Room
{
public:
	Room(RoomData roomData, RoomState roomState);
	Room();

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	void close();
	vector<LoggedUser> getAllUsers() const;
	RoomState getRoomState() const;
	bool didGameStart() const;
	bool isClosed() const;
	unsigned int getId() const;
	void setId(unsigned int id);
	friend void to_json(json& j, const Room& room);
private:
	RoomData m_roomdata;
	RoomState m_roomstate;
};
