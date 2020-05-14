#include "pch.h"
#include "SqliteDataBase.h"

std::unordered_map<string, string> SqliteDataBase::users_list;
bool SqliteDataBase::moreData = false;

SqliteDataBase::SqliteDataBase()
{
	if (openDB())
	{
		throw std::exception("Error opening Sqlite Database");
	}
}

/*
Usage: checks whether a user exists in the DB.
Input: string username.
Output: bool.
*/
bool SqliteDataBase::doesUserExist(string username)
{
	moreData = false;
	std::string sqlStatement = "select * from users where username like '" + username + "';";
	send_query(sqlStatement);

	//returns if the username can be found in the map of users.
	return users_list.find(username) != users_list.end();
}

/*
Usage: checks if the password matches the username.
Input: string username, string password.
Output: bool.
*/
bool SqliteDataBase::doesPasswordMatch(string username, string password)
{
	moreData = false;
	std::string sqlStatement = "select * from users where username like '" + username + "';";
	send_query(sqlStatement);
	//returns whether the user exists and if the password matched the username
	return doesUserExist(username) && users_list[username] == password;
}

/*
Usage: adds a new user to the DB
Input: string username, string password, string email.
Output: void.
*/
void SqliteDataBase::addNewUser(string username, string password, string email)
{
	std::string command = "insert into users (username, password, email) values ('" + username + "', '" + password + "', '" + email + "');";
	send_query(command);
}

/*
Usage: opens the DB.
Input: none.
Output: bool.
*/
bool SqliteDataBase::openDB()
{
	string command;
	this->dbFileName = "DBFile.sqlite";

	int doesFileExist = _access(this->dbFileName, 0);
	//opens the file
	int res = sqlite3_open(this->dbFileName, &this->db);
	if (res != SQLITE_OK)
	{
		this->dbFileName = nullptr;
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	//if the table does not exist
	if (doesFileExist)
	{
		//user table
		command = "create table users if not exists (username text primary key not null, password text not null, email text not null);";
		send_query(command);
	}
	SqliteDataBase::moreData = false;
	return true;
}

/*
Usage: the users callback.
Input: data, argc, argv, azcolname.
Output: int.
*/
int SqliteDataBase::users_callback(void* data, int argc, char** argv, char** azColName)
{
	//to make sure it doesnt clear the list when it goes back into the function to add another user.
	if (!SqliteDataBase::moreData)
		SqliteDataBase::users_list.clear();

	string username;
	string password;

	//gets all of the usernames and password and adds them into the map.
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "username")
			username = argv[i];
		else if (std::string(azColName[i]) == "password")
			password = argv[i];
	}

	//adds the new user to the list.
	SqliteDataBase::users_list[username] = password;
	SqliteDataBase::moreData = true;
	return 0;
}

void SqliteDataBase::send_query(std::string command)
{
	char* errMessage = nullptr;
	sqlite3_exec(this->db, command.c_str(), nullptr, nullptr, &errMessage);
}
