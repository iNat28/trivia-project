#pragma once
#include "pch.h"
#include "LoggedUser.h"

struct UserHighScore
{
	UserHighScore(string username, int numPoints);
	UserHighScore();

	string username;
	int numPoints;
};

struct UserStats
{
	UserStats(string username, int numPoints, int numTotalGames, int numCorrectAnswers, int numWrongAnswers, int averageAnswerTime);
	UserStats();
	
	string username;
	int numPoints;
	int numTotalGames;
	int numCorrectAnswers;
	int numWrongAnswers;
	int averageAnswerTime;
};

void to_json(json& j, const UserHighScore& userHighScore);
void to_json(json& j, const UserStats& userStats);

//struct RecordTable
//{
//	RecordTable(std::vector<std::pair<string, int>> table);
//	RecordTable();
//
//	std::array<UserStats, 5> userRecordTable;
//};

//struct PersonalUserGameStats
//{
//	PersonalUserGameStats(string username, vector<UserStats> allGames);
//	PersonalUserGameStats();
//
//	string username;
//	vector<UserStats> allGames;
//	RecordTable recordTable;
//};