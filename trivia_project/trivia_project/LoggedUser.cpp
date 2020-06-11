#include "pch.h"
#include "LoggedUser.h"

LoggedUser::LoggedUser(string username) : 
	username(username), numCorrectAnswers(0), answerTime(0), numPoints(0)
{
}

LoggedUser::LoggedUser()
{
}
//TODO: add the rest of the vars into the json funcions
void to_json(json& j, const LoggedUser& loggedUser)
{
	j[Keys::username] = loggedUser.username;
}

void from_json(const json& j, LoggedUser& loggedUser)
{
	loggedUser.username = j[Keys::username];
}