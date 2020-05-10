#include "pch.h"
#pragma once
#include <iostream>
#include "sqlite3.h"
#include <io.h>

using std::string;

class IDatabase
{
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username, string password) = 0;
	virtual void addNewUser(string username, string password, string email) = 0;
};