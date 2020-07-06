#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "Exception.h"
#include "sqlite3.h"
#include "Keys.h"
#include "Statistics.h"
#include "Game.h"

#define QUESTIONS_FILE  "questions.txt"
#define BUFFER_SIZE 1024

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();

	//queries
	virtual bool doesUserExist(string username) const override;
	virtual bool doesPasswordMatch(string username, string password) const override;
	virtual void addNewUser(string username, string password, string email) const override;
	static int users_callback(void* data, int argc, char** argv, char** azColName);
	static int statistics_callback(void* data, int argc, char** argv, char** azColName);
	static int int_callback(void* data, int argc, char** argv, char** azColName);

	void send_query(std::string command, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr) const;

	void openQuestionsFile();
	vector<Question> getQuestionsIntoVectorFormat(string questionsStr);
	void addToDB(vector<Question> questions);

	//statistics
	virtual int getHighestRoomId() const override;
	virtual void addGameStats(LoggedUser username, PlayerResults playerResults) override;
	virtual UserStats getUserStats(string username) const override;
	virtual HighScores getHighScores() const override;
	
private:
	void openDB();

	sqlite3* db;
	const char* dbFileName;
	static const unsigned int HIGH_SCORE_NUMS = 3;

	//Change to struct
	static std::unordered_map<string, string> m_usersList;
	static std::vector<UserStats> m_usersStats;
	//variable for multiple users
	static bool moreData;
	static int highestRoomId;
};

//https://opentdb.com/api.php?amount=10
