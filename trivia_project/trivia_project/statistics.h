#pragma once
#include "pch.h"

struct GameStats
{
	GameStats(int roomId, string averageAnswerTime, int numCorrectAnswers, int numTotalAnswers, int numPoints);
	GameStats();

	int roomId;
	string averageAnswerTime;
	int numCorrectAnswers;
	int numTotalAnswers;
	int numPoints;
};

struct PersonalUserGameStats
{
	PersonalUserGameStats(string username, vector<GameStats> allGames);
	PersonalUserGameStats();

	string username;
	vector<GameStats> allGames;
};

struct RecordTable
{
	RecordTable(string username, std::array<GameStats, 5> table);
	RecordTable();

	string username;
	std::array<GameStats, 5> userRecordTable;
};
