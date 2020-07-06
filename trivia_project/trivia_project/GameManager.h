#pragma once
#include "pch.h"
#include "Game.h"
#include "IDatabase.h"

class GameManager
{
public:
	GameManager(IDatabase& database);

	Game& createGame(Room& room);
	void deleteGame(Game game);
private:
	IDatabase& m_database;
	vector<Game> m_games;
};

