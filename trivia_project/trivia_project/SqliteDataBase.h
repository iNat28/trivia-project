#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "Exception.h"
#include "sqlite3.h"
#include <map>

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();

	//queries
	virtual bool doesUserExist(string username) const override;
	virtual bool doesPasswordMatch(string username, string password) const override;
	virtual void addNewUser(string username, string password, string email) const override;

	static int users_callback(void* data, int argc, char** argv, char** azColName);

	void send_query(std::string command, int(*callback)(void*, int, char**, char**) = nullptr) const;

	bool openDB();

	sqlite3* db;
	const char* dbFileName;

	static std::unordered_map<string, string> users_list;
	//variable for multiple users
	static bool moreData;
};

