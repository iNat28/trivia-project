#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "statistics.h"

class StatisticsManager
{
public:
	StatisticsManager(IDatabase& database);

	RecordTable getStatistics();
private:
	IDatabase& m_database;
};

