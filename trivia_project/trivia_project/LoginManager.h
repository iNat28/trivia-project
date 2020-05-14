#pragma once
#include "pch.h"
#include "SqliteDataBase.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class LoginManager
{
public:
	LoginManager(IDatabasePtr database);

	void signup(string username, string password, string email);
	void login(string username, string password);
	void logout(string username);

private:
	IDatabasePtr m_database;
	vector<LoggedUser> m_loggedUsers;
};

