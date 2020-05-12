#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "sqlite3.h"
#include <map>

static std::unordered_map<string, string> users_list;

class SqliteDataBase : 
	public IDatabase
{
public:
	SqliteDataBase() { openDB(); }

	//queries
	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);
	virtual void addNewUser(string username, string password, string email);


	bool openDB();

	sqlite3* db;
	const char* dbFileName;
};


int users_callback(void* data, int argc, char** argv, char** azColName);
