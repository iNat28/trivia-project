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

void to_json(json& j, const UserStats& userStats)
{
	j[Keys::roomId] = userStats.roomId;
	j[Keys::numQuestionsAsked] = userStats.totalQuestions;
	//TODO: Add key
	j["user"] = userStats.user;
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