#pragma once
#include "pch.h"
#include "Game.h"
#include "IDatabase.h"

class GameManager
{
public:
	GameManager(IDatabase& database);

	Game& createGame(Room& room, std::queue<Question> questions);
	void deleteGame(Game& game);
	Game& getGame(Room& room);
	map<LoggedUser, PlayerResults> getGameResults(Game& game, LoggedUser user);
	void removePlayer(Game& game, LoggedUser user);
private:
	IDatabase& m_database;
	vector<Game> m_games;
};

