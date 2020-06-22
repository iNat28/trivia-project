#include "pch.h"
#include "LoggedUser.h"

LoggedUser::LoggedUser(string username) :
	username(username)
{
}

LoggedUser::LoggedUser()
{
}

//TODO: add the rest of the vars into the json funcions and into the keys
void to_json(json& j, const LoggedUser& loggedUser)
{
	j[Keys::username] = loggedUser.username;
}