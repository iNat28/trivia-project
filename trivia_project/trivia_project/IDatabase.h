
#pragma once
#include "pch.h"
#include "sqlite3.h"
#include "statistics.h"

using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(string username) const = 0;
	virtual bool doesPasswordMatch(string username, string password) const = 0;
	virtual void addNewUser(string username, string password, string email) const = 0;
	virtual void addGameStats(string username, GameStats gameStats) = 0;
};