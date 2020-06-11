#pragma once
#include "pch.h"
#include "Room.h"
#include <string>
#include <iostream>
#include <map>

using std::string;
using std::vector;
using std::map;

class RoomManager
{
public:
	void createRoom(LoggedUser user, RoomData roomData);
	void deleteRoom(unsigned int id);
	bool getRoomState(unsigned int id) const;
	Room& getRoom(unsigned int id);
	vector<LoggedUser> getUsersInRoom(unsigned int id) const;
	vector<Room> getRooms() const;
private:
	map<int, Room> m_rooms;

	const Room& _getRoom(unsigned int id) const;
};

