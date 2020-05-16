
#pragma once
#include "pch.h"
#include <iostream>
#include "sqlite3.h"
#include <io.h>

using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(string username) const = 0;
	virtual bool doesPasswordMatch(string username, string password) const = 0;
	virtual void addNewUser(string username, string password, string email) const = 0;
};