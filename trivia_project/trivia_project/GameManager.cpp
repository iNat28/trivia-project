#include "pch.h"
#include "GameManager.h"

GameManager::GameManager(IDatabase& database)
{
}

Game GameManager::createGame(Room)
{
	return Game();
}

void GameManager::deleteGame(RoomData)
{
}
