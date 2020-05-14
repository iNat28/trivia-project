#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "sqlite3.h"
#include <map>

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();

	//queries
	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);
	virtual void addNewUser(string username, string password, string email);

	static int users_callback(void* data, int argc, char** argv, char** azColName);

	void send_query(std::string command);

	bool openDB();

	sqlite3* db;
	const char* dbFileName;

	static std::unordered_map<string, string> users_list;
	//variable for multiple users
	static bool moreData;
};

