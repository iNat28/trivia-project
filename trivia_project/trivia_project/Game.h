#pragma once
#include "pch.h"
#include "statistics.h"
#include "Room.h"

#define ANSWERS_COUNT 4
#define INCORRECT_ANSWERS_COUNT ANSWERS_COUNT - 1
#define POINT_MULTIPLIER 100

struct Question
{
	Question(string category, unsigned int difficulty, string question, vector<string> answers, unsigned int correctAnswerIndex);
	Question();

	string category;
	unsigned int difficulty;
	string question;
	vector<string> answers;
	unsigned int correctAnswerIndex;
	
	static unsigned int getDifficulty(string difficulty);
};

typedef vector<Question> Questions;

void to_json(json& j, const Question& question);
void from_json(const json& j, Question& question);

struct GameData
{
	GameData(PlayerResults playerResults, bool gotResults);
	GameData();

	PlayerResults playerResults;
	bool gotResults; //If the player recieved the data
};

class Game
{
public:
	Game(Room& room, Questions questions);
	Game();

	const Question& getQuestion() const;
	unsigned int submitAnswer(LoggedUser user, int answerIndex, unsigned int answerTime);
	void removePlayer(LoggedUser user);
	vector<UserResults> getGameResults(LoggedUser user);
	vector<UserResults> getGameResults();
	bool allPlayersGotResults() const;
	bool operator==(const Game& other) const;
	bool operator==(const Room& other) const;

	//Needed for unknown reason
	Game& operator=(const Game& other);
private:
	Questions m_questions;
	map<LoggedUser, GameData> m_players;
	Room& m_room;
};