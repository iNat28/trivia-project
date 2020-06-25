#include "pch.h"
#include "Statistics.h"

UserStats::UserStats(string username, int numPoints, int numTotalGames, int numCorrectAnswers, int numWrongAnswers, int averageAnswerTime) :
	username(username), numPoints(numPoints), numTotalGames(numTotalGames), numCorrectAnswers(numCorrectAnswers), numWrongAnswers(numWrongAnswers), averageAnswerTime(averageAnswerTime)
{
}

UserStats::UserStats() :
	numPoints(0), numTotalGames(0), numCorrectAnswers(0), numWrongAnswers(0), averageAnswerTime(0)
{
}

UserHighScore::UserHighScore(string username, int numPoints) : 
	username(username), numPoints(numPoints)
{
}

UserHighScore::UserHighScore() : 
	numPoints(0)
{
}

void to_json(json& j, const UserHighScore& userHighScore)
{
	j[Keys::username] = userHighScore.username;
	j[Keys::numPoints] = userHighScore.numPoints;
}

void to_json(json& j, const UserStats& userStats)
{
	j[Keys::username] = userStats.username;
	j[Keys::numPoints] = userStats.numPoints;
	j[Keys::numTotalGames] = userStats.numTotalGames;
	j[Keys::numCorrectAnswers] = userStats.numCorrectAnswers;
	j[Keys::numWrongAnswers] = userStats.numWrongAnswers;
	j[Keys::averageAnswerTime] = userStats.averageAnswerTime;
}