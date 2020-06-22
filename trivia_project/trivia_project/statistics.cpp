#include "pch.h"
#include "Statistics.h"

UserStats::UserStats(LoggedUser user, unsigned int roomId, unsigned int totalQuestions) :
	user(user), roomId(roomId), totalQuestions(totalQuestions)
{
}

UserStats::UserStats(string username, int numPoints, int numTotalGames, int numCorrectAnswers, int numWrongAnswers, int averageAnswerTime) :
	username(username), numPoints(numPoints), numTotalGames(numTotalGames), numCorrectAnswers(numCorrectAnswers), numWrongAnswers(numWrongAnswers), averageAnswerTime(averageAnswerTime)
{
}

UserStats::UserStats() :
	numPoints(0), numTotalGames(0), numCorrectAnswers(0), numWrongAnswers(0), averageAnswerTime(0)
{
}

void to_json(json& j, const UserStats& userStats)
{
	
}

unsigned int UserStats::getAverageAnswerTime()
{
	return this->user.answerTime / this->totalQuestions;
}

RecordTable::RecordTable(std::array<UserStats, 5> table) : userRecordTable(table)
{
}

RecordTable::RecordTable()
{
}

PersonalUserGameStats::PersonalUserGameStats(string username, vector<UserStats> allGames) : username(username), allGames(allGames)
{
}

PersonalUserGameStats::PersonalUserGameStats()
{
}