#pragma once
#include "pch.h"

struct GameStats
{
	GameStats(int numPoints);
	GameStats();

	int numPoints;
};

struct RecordTable
{
	RecordTable(vector <GameStats> table);
	RecordTable();

	vector<GameStats> userRecordTable;
};
