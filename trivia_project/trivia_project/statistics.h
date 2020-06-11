#pragma once
#include "pch.h"
#include "LoggedUser.h"

struct UserStats
{
	UserStats(LoggedUser username, unsigned int roomId, unsigned int totalQuestions);
	UserStats();
	
	unsigned int getAverageAnswerTime();

	LoggedUser user;
	unsigned int roomId;
	unsigned int totalQuestions;
};

struct PersonalUserGameStats
{
	PersonalUserGameStats(string username, vector<UserStats> allGames);
	PersonalUserGameStats();

	string username;
	vector<UserStats> allGames;
};

struct RecordTable
{
	RecordTable(string username, std::array<UserStats, 5> table);
	RecordTable();

	string username;
	std::array<UserStats, 5> userRecordTable;
};
