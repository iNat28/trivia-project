#pragma once
#include "pch.h"
#include "LoggedUser.h"

struct UserHighScore
{
	UserHighScore(string username, unsigned int numPoints);
	UserHighScore();

	string username;
	int numPoints;
};

typedef std::vector<UserHighScore> HighScores;

struct PlayerResults
{
	PlayerResults(unsigned int numCorrectAnswers, unsigned int numWrongAnswers, unsigned int averageAnswerTime, unsigned int numPoints);
	PlayerResults();

	unsigned int numCorrectAnswers;
	unsigned int numWrongAnswers;
	unsigned int averageAnswerTime;
	unsigned int numPoints;
};

struct UserStats
{
	UserStats(PlayerResults playerResults, string username, unsigned int numTotalGames);
	UserStats();
	
	string username;
	PlayerResults playerResults;
	int numTotalGames;
};

void to_json(json& j, const UserHighScore& userHighScore);
void to_json(json& j, const PlayerResults& playerResults);
void to_json(json& j, const UserStats& userStats);