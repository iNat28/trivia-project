#include "pch.h"
#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase& database) :
	m_database(database)
{
}

PersonalUserGameStats StatisticsManager::getStatistics(string username)
{
	return this->m_database.getAllTimeGameStats(username);
}
