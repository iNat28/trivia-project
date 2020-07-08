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
	PlayerResults playerResults;
	bool gotData; //If the player recieved the data
};

class Game
{
public:
	Game(Room& room, Questions questions);
	Game();

	const Question& getQuestion() const;
	unsigned int submitAnswer(LoggedUser user, unsigned int answerIndex, unsigned int answerTime);
	PlayerResults removePlayer(LoggedUser user);
	std::pair<map<LoggedUser, PlayerResults>, bool> getGameResults(LoggedUser user);
	bool empty() const;
	bool operator==(const Game& other) const;
	bool operator==(const Room& other) const;
	Game& operator=(const Game& other);
private:
	Questions m_questions;
	map<LoggedUser, GameData> m_players;
	Room& m_room;
};