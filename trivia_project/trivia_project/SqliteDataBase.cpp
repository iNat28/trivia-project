#include "pch.h"
#include "SqliteDataBase.h"

std::unordered_map<string, string> SqliteDataBase::users_list;
bool SqliteDataBase::moreData = false;

SqliteDataBase::SqliteDataBase()
{
	if (!openDB())
	{
		throw std::exception("Error opening Sqlite Database");
	}
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
	return users_list.find(username) != users_list.end();
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
	return doesUserExist(username) && users_list[username] == password;
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
		command = "create table if not exists users (username text primary key not null, password text not null, email text not null);";
		send_query(command);

		//questions table
		command = "create table if not exists questions (question text primary key not null, category text, difficulty text, correct_answer text not null, incorrect_answer1 text not null, incorrect_answer2 text, incorrect_answer3 text);";
		send_query(command);
		//adding the questions
		openQuestionsFile();
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

void SqliteDataBase::send_query(std::string command, int(*callback)(void*, int, char**, char**)) const
{
	char* errMessage = nullptr;
	if (SQLITE_OK != sqlite3_exec(this->db, command.c_str(), callback, nullptr, &errMessage))
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

	//vector<map<string, string>> questionList;
	//map<string, string> question;

	//for (int i = 0; i <= questions.size();)
	//{
	//	while (i <= questions.size())
	//	{
	//		if (i > 0 && questions[i - 1] != '}')
	//		{
	//			questionInfo += questions[i];
	//		}
	//	}
	//	question["category"] = "";
	//	for (int j = questionInfo.find("category") + 11; j != '/"'; j++)
	//	{
	//		question["category"] += questionInfo[j];
	//	}
	//	question["difficulty"] = "";
	//	for (int j = questionInfo.find("difficulty") + 13; j != '/"'; j++)
	//	{
	//		question["difficulty"] += questionInfo[j];
	//	}
	//	question["question"] = "";
	//	for (int j = questionInfo.find("question") + 11; j != '/"'; j++)
	//	{
	//		question["question"] += questionInfo[j];
	//	}
	//	question["correct_answer"] = "";
	//	for (int j = questionInfo.find("correct_answer") + 17; j != '/"'; j++)
	//	{
	//		question["correct_answer"] += questionInfo[j];
	//	}
	//	question["incorrect_answer1"] = "";
	//	int j;
	//	for (j = questionInfo.find("incorrect_answers") + 21; j != '/"'; j++)
	//	{
	//		question["incorrect_answer1"] += questionInfo[j];
	//	}
	//	question["incorrect_answer2"] = "";
	//	question["incorrect_answer3"] = "";
	//	if (questionInfo[j + 1] != ']')
	//	{
	//		for (j += 3; j != '/"'; j++)
	//		{
	//			question["incorrect_answer2"] += questionInfo[j];
	//		}
	//		for (j += 3; j != '/"'; j++)
	//		{
	//			question["incorrect_answer3"] += questionInfo[j];
	//		}
	//	}
	//	questionList.push_back(question);
	//}
	return questionList;
}


void SqliteDataBase::addToDB(vector<Question> questionsList)
{
	auto buffer = std::make_unique<char[]>(BUFFER_SIZE + 1);

	for (const auto& question : questionsList)
	{
		sprintf_s(buffer.get(), BUFFER_SIZE,
			"insert into questions(question, category, difficulty, correct_answer, incorrect_answer1, incorrect_answer2, incorrect_answer3) values('%s', '%s', '%s', '%s', '%s', '%s', '%s');",
			question.question.c_str(),
			question.category.c_str(),
			question.difficulty.c_str(),
			question.correctAnswer.c_str(),
			question.incorrectAnswers[0].c_str(),
			question.incorrectAnswers[1].c_str(),
			question.incorrectAnswers[2].c_str()
		);

		send_query(buffer.get());
	}
}

inline void from_json(const json& j, Question& question)
{
	question = Question(
		j[Keys::category],
		j[Keys::difficulty],
		j[Keys::question],
		j[Keys::correctAnswer],
		std::array<string, 3>{
			j[Keys::incorrectAnswer1],
			j[Keys::incorrectAnswer2],
			j[Keys::incorrectAnswer3]
		}
	);
}

Question::Question(string category, string difficulty, string question, string correctAnswer, std::array<string, 3> incorrectAnswers) :
	category(category), difficulty(difficulty), question(question), correctAnswer(correctAnswer), incorrectAnswers(incorrectAnswers)
{
}

Question::Question()
{
}