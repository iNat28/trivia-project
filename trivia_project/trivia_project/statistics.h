#pragma once
#include "pch.h"

struct gameStats
{
	gameStats(int numPoints);
	gameStats();

	int numPoints;
};

struct recordTable
{
	recordTable(vector <gameStats> table);
	recordTable();

	vector<gameStats> userRecordTable;
};
