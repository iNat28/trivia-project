#include "pch.h"
#include "LoggedUser.h"

LoggedUser::LoggedUser(string username) : 
	m_username(username)
{
}

LoggedUser::LoggedUser()
{
}

void to_json(json& j, const LoggedUser& loggedUser)
{
	j[Keys::username] = loggedUser.m_username;
}

void from_json(const json& j, LoggedUser& loggedUser)
{
	loggedUser.m_username = j[Keys::username];
}