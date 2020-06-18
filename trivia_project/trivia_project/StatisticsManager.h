#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "statistics.h"

class StatisticsManager
{
public:
	StatisticsManager(IDatabase& database);

	PersonalUserGameStats getStatistics(string username);
private:
	IDatabase& m_database;
};

