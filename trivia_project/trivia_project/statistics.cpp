#include "pch.h"
#include "Statistics.h"

GameStats::GameStats(int numPoints) : numPoints(numPoints)
{
}

GameStats::GameStats() : 
	numPoints(0)
{
}

RecordTable::RecordTable(vector<GameStats> table) : userRecordTable(table)
{
}

RecordTable::RecordTable()
{
}
