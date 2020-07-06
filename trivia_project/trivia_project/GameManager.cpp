#include "pch.h"
#include "GameManager.h"

GameManager::GameManager(IDatabase& database) : 
	m_database(database)
{
}

Game& GameManager::createGame(Room& room)
{
	//TODO: Change
	return this->m_games[0];
}

void GameManager::deleteGame(Game game)
{
}
