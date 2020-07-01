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