#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "statistics.h"

class StatisticsManager
{
public:
	recordTable getStatistics();
private:
	IDatabase& m_database;
};

