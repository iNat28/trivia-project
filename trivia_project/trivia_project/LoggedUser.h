#pragma once
#include "pch.h"
#include "Keys.h"

struct LoggedUser
{
	LoggedUser(string username);
	LoggedUser();

	string m_username;
};

void to_json(json& j, const LoggedUser& loggedUser);
void from_json(const json& j, LoggedUser& loggedUser);