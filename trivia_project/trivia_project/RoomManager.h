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
	void createRoom(LoggedUser user);
	void deleteRoom(int id);
	bool getRoomState(int id) const;
	vector<Room> getRooms() const;
private:
	map<int, Room> m_rooms;
};

