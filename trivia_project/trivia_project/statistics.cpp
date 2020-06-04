#include "pch.h"
#include "statistics.h"

gameStats::gameStats(int numPoints) : numPoints(numPoints)
{
}

gameStats::gameStats()
{
}

recordTable::recordTable(vector<gameStats> table) : userRecordTable(table)
{
}

recordTable::recordTable()
{
}
