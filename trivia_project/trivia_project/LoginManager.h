#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager(IDatabase& database);

	void signup(string username, string password, string email);
	void login(string username, string password);
	void logout(string username);

private:
	IDatabase& m_database;
	vector<LoggedUser> m_loggedUsers;
};

