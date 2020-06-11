#include "pch.h"
#include "Statistics.h"

GameStats::GameStats(int roomId, string averageAnswerTime, int numCorrectAnswers, int numTotalAnswers, int numPoints) : roomId(roomId), averageAnswerTime(averageAnswerTime), numCorrectAnswers(numCorrectAnswers), numTotalAnswers(numTotalAnswers), numPoints(numPoints)
{
}

GameStats::GameStats() : 
	numPoints(0)
{
}

RecordTable::RecordTable(string username, std::array<GameStats, 5> table) : username(username), userRecordTable(table)
{
}

RecordTable::RecordTable()
{
}

PersonalUserGameStats::PersonalUserGameStats(string username, vector<GameStats> allGames) : username(username), allGames(allGames)
{
}

PersonalUserGameStats::PersonalUserGameStats()
{
}
