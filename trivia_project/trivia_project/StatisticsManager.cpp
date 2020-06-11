#include "pch.h"
#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase& database) :
	m_database(database)
{
}

RecordTable StatisticsManager::getStatistics()
{
	return RecordTable();
}
