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

struct RecordTable
{
	RecordTable(std::array<UserStats, 5> table);
	RecordTable();

	std::array<UserStats, 5> userRecordTable;
};

struct PersonalUserGameStats
{
	PersonalUserGameStats(string username, vector<UserStats> allGames);
	PersonalUserGameStats();

	string username;
	vector<UserStats> allGames;
	RecordTable recordTable;
};

void to_json(json& j, const UserStats& userStats);