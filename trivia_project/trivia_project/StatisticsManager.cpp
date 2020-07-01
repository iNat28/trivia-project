#include "pch.h"
#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase& database) :
	m_database(database)
{
}

UserStats StatisticsManager::getUserStats(string username)
{
	return this->m_database.getUserStats(username);
}

HighScores StatisticsManager::getHighScores()
{
	return this->m_database.getHighScores();
}
