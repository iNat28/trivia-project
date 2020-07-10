#include "pch.h"
#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase& database) :
	m_database(database)
{
}

UserStats StatisticsManager::getUserStats(LoggedUser& user)
{
	return this->m_database.getUserStats(user);
}

HighScores StatisticsManager::getHighScores()
{
	return this->m_database.getHighScores();
}
