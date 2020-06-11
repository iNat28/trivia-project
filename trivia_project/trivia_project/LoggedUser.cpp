#include "pch.h"
#include "LoggedUser.h"

LoggedUser::LoggedUser(string username) : 
	username(username)
{
}

LoggedUser::LoggedUser()
{
}

void to_json(json& j, const LoggedUser& loggedUser)
{
	j[Keys::username] = loggedUser.username;
}

void from_json(const json& j, LoggedUser& loggedUser)
{
	loggedUser.username = j[Keys::username];
}