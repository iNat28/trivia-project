#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "statistics.h"

class StatisticsManager
{
public:
	RecordTable getStatistics();
private:
	IDatabase& m_database;
};

