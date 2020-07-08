#include "pch.h"
#include "GameManager.h"

GameManager::GameManager(IDatabase& database) : 
	m_database(database)
{
}

Game& GameManager::createGame(Room& room, Questions questions)
{
	this->m_games.push_back(Game(room, questions));

	return this->m_games.back();
}

void GameManager::deleteGame(Game& game)
{
	for (auto userAndResults : game.getGameResults())
	{
		this->m_database.addGameStats(userAndResults.user, userAndResults.playerResults);
	}

	for (auto it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		if (*it == game)
		{
			this->m_games.erase(it);
			return;
		}
	}
}

Game& GameManager::getGame(Room& room)
{
	for (auto& game : this->m_games)
	{
		if (game == room)
		{
			return game;
		}
	}
}
//
//map<LoggedUser, PlayerResults> GameManager::getGameResults(Game& game, LoggedUser user)
//{
//	auto gameResults = game.getGameResults(user);
//
//	for (const auto& playerResult : gameResults)
//	{
//		this->m_database.addGameStats(playerResult.first, playerResult.second);
//	}
//
//	if (game.allPlayersGotResults())
//	{
//		this->deleteGame(game);
//	}
//
//	return gameResults;
//}

Questions GameManager::getQuestions(unsigned int questionsCount) const
{
	return this->m_database.getQuestions(questionsCount);
}
