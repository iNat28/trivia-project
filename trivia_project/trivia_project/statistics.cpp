#include "pch.h"
#include "Statistics.h"

UserStats::UserStats(LoggedUser user, unsigned int roomId, unsigned int totalQuestions) :
	user(user), roomId(roomId), totalQuestions(totalQuestions)
{
}

UserStats::UserStats() : 
	roomId(0), totalQuestions(0)
{
}

unsigned int UserStats::getAverageAnswerTime()
{
	return this->user.answerTime / this->totalQuestions;
}

RecordTable::RecordTable(string username, std::array<UserStats, 5> table) : username(username), userRecordTable(table)
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
