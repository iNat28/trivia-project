#include "pch.h"
#include "Statistics.h"

GameStats::GameStats(int numPoints) : numPoints(numPoints)
{
}

GameStats::GameStats()
{
}

RecordTable::RecordTable(vector<GameStats> table) : userRecordTable(table)
{
}

RecordTable::RecordTable()
{
}
