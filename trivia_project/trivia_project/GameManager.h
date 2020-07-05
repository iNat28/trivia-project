#pragma once

#include "pch.h"
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"

class GameManager
{
public:
	GameManager(IDatabase& database);

	Game createGame(Room);
	void deleteGame(RoomData);

private:
	IDatabase& m_database;
	vector<Game> m_games;
};

