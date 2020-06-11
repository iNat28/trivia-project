#include "pch.h"
#include "SqliteDataBase.h"

std::unordered_map<string, string> SqliteDataBase::m_usersList;
std::vector<UserStats> SqliteDataBase::m_gamesList;
bool SqliteDataBase::moreData = false;

SqliteDataBase::SqliteDataBase()
{
	this->openDB();
}

/*
Usage: checks whether a user exists in the DB.
Input: string username.
Output: bool.
*/
bool SqliteDataBase::doesUserExist(string username) const
{
	moreData = false;
	std::string sqlStatement = "select * from users where username = '" + username + "';";
	send_query(sqlStatement, users_callback);
	
	//returns if the username can be found in the map of users.
	return m_usersList.find(username) != m_usersList.end();
}

/*
Usage: checks if the password matches the username.
Input: string username, string password.
Output: bool.
*/
bool SqliteDataBase::doesPasswordMatch(string username, string password) const
{
	moreData = false;
	std::string sqlStatement = "select * from users where username = '" + username + "';";
	send_query(sqlStatement, users_callback);
	//returns whether the user exists and if the password matched the username
	return doesUserExist(username) && m_usersList[username] == password;
}

/*
Usage: adds a new user to the DB
Input: string username, string password, string email.
Output: void.
*/
void SqliteDataBase::addNewUser(string username, string password, string email) const
{
	std::string command = "insert into users (username, password, email) values ('" + username + "', '" + password + "', '" + email + "');";
	send_query(command);
}

/*
Usage: opens the DB.
Input: none.
Output: bool.
*/
void SqliteDataBase::openDB()
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
		throw std::exception("Error opening Sqlite Database");
	}

	//if the table does not exist
	if (doesFileExist)
	{
		//user table
		command = "create table if not exists users (username text primary key not null, password text not null, email text not null);";
		send_query(command);

		//statistics table
		command = "create table if not exists statistics (username text primary key not null, roomId integer not null, answerTime integer not null, numCorrectAnswers integer not null, numTotalAnswers integer not null, numPoints integer not null);";
		send_query(command);

		//questions table
		command = "create table if not exists questions (question text primary key not null, category text, difficulty text, correct_answer text not null, incorrect_answer1 text not null, incorrect_answer2 text, incorrect_answer3 text);";
		send_query(command);
		//adding the questions
		openQuestionsFile();
	}

	SqliteDataBase::moreData = false;
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
		SqliteDataBase::m_usersList.clear();

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
	SqliteDataBase::m_usersList[username] = password;
	SqliteDataBase::moreData = true;
	return 0;
}

int SqliteDataBase::statistics_callback(void* data, int argc, char** argv, char** azColName)
{
	if (!SqliteDataBase::moreData)
		SqliteDataBase::m_gamesList.clear();

	UserStats userStats;
	
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "username")
			userStats.user.username = argv[i];
		else if (std::string(azColName[i]) == "roomId")
			userStats.roomId = atoi(argv[i]);
		else if (std::string(azColName[i]) == "answerTime")
			userStats.user.answerTime = atoi(argv[i]);
		else if (std::string(azColName[i]) == "numCorrectAnswers")
			userStats.user.numCorrectAnswers = atoi(argv[i]);
		else if (std::string(azColName[i]) == "numTotalAnswers")
			userStats.totalQuestions = atoi(argv[i]);
		else if (std::string(azColName[i]) == "numPoints")
			userStats.user.numPoints = atoi(argv[i]);
	}
		
	SqliteDataBase::m_gamesList.push_back(userStats);
	SqliteDataBase::moreData = true;
	return 0;
}

int SqliteDataBase::int_callback(void* data, int argc, char** argv, char** azColName)
{
	int* intReturn = static_cast<int*>(data);

	if (intReturn != nullptr)
	{
		*intReturn = atoi(argv[0]);
	}

	return 0;
}

void SqliteDataBase::send_query(std::string command, int(*callback)(void*, int, char**, char**), void* data) const
{
	char* errMessage = nullptr;
	if (SQLITE_OK != sqlite3_exec(this->db, command.c_str(), callback, data, &errMessage))
	{
		Exception::ex << errMessage;
		sqlite3_free(errMessage);
		throw Exception();
	}
}

void SqliteDataBase::openQuestionsFile()
{
	std::ifstream file(QUESTIONS_FILE);
	string buffer;
	vector<Question> questionList;
	file >> buffer;
	
	questionList = getQuestionsIntoVectorFormat(buffer);
	addToDB(questionList);
}

vector<Question> SqliteDataBase::getQuestionsIntoVectorFormat(string questionsStr)
{
	string questionInfo;
	json questionList(questionsStr);

	vector<Question> questions = questionList;
	return questions;
}


void SqliteDataBase::addToDB(vector<Question> questionsList)
{
	sstream buffer;

	for (const auto& question : questionsList)
	{
		buffer << "insert into questions(question, category, difficulty, correct_answer, incorrect_answer1, incorrect_answer2, incorrect_answer3) values(" <<
			question.question << ", " <<
			question.category << ", " <<
			question.difficulty << ", " <<
			question.correctAnswer << ", " <<
			question.incorrectAnswers[0] << ", " <<
			question.incorrectAnswers[1] << ", " <<
			question.incorrectAnswers[2] << "')";

		send_query(buffer.str().c_str());
		buffer.str("");
	}
}

int SqliteDataBase::getHighestRoomId() const
{
	int highestRoomId = 0;

	SqliteDataBase::moreData = false;
	std::string sqlStatement = "select * from statistics order by roomId DESC limit 1;";
	send_query(sqlStatement, int_callback, &highestRoomId);

	return highestRoomId;
}

void SqliteDataBase::addGameStats(UserStats gameStats)
{
	sstream buffer;

	buffer << "insert into statistics(username, roomId, answerTime, numCorrectAnswers, numTotalAnswers, numPoints) values('" <<
		gameStats.user.username << "', " <<
		gameStats.roomId << "', " <<
		gameStats.user.answerTime << "', " <<
		gameStats.user.numCorrectAnswers << "', " <<
		gameStats.totalQuestions << "', " <<
		gameStats.user.numPoints << "')";

	send_query(buffer.str().c_str());
}

PersonalUserGameStats SqliteDataBase::getAllTimeGameStats(string username) const
{
	PersonalUserGameStats allUserGameStats;
	SqliteDataBase::moreData = false;
	sstream buffer;

	buffer << "select * from statistics where username = '" << username << "')";
	send_query(buffer.str().c_str(), statistics_callback);
	
	for (auto& game : m_gamesList)
	{
		allUserGameStats.allGames.push_back(game);
	}
	
	allUserGameStats.recordTable = getFiveBestUserGames(username);

	return allUserGameStats;
}

RecordTable SqliteDataBase::getFiveBestUserGames(string username) const
{
	RecordTable records;
	SqliteDataBase::moreData = false;
	sstream buffer;

	buffer << "select * from statistics where username = '" << username << "' order by numPoints DESC limit 5;";
	send_query(buffer.str().c_str(), statistics_callback);

	int i = 0;
	for (auto& game : m_gamesList)
	{
		records.userRecordTable[i] = game;
		i++;
	}
	return records;
}