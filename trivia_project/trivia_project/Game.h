#pragma once
#include "pch.h"
#include "statistics.h"
#include "Room.h"

#define ANSWERS_COUNT 4
#define INCORRECT_ANSWERS_COUNT ANSWERS_COUNT - 1

struct Question
{
	Question(string category, string difficulty, string question, std::array<string, 4> answers, unsigned int correctAnswerIndex);
	Question();

	string category;
	string difficulty;
	string question;
	std::array<string, ANSWERS_COUNT> answers;
	unsigned int correctAnswerIndex;
};

void to_json(json& j, const Question& question);
void from_json(const json& j, Question& question);

struct GameData
{
	GameData(Question currentQuestion, PlayerResults playerResults);
	
	Question currentQuestion;
	PlayerResults playerResults;
};

void to_json(json& j, const Question& question);

class Game
{
public:
	Game(Room& room);

	Question getQuestion();
	unsigned int submitAnswer(LoggedUser user, unsigned int answerChoice);
	void removePlayer(LoggedUser);
	map<LoggedUser, PlayerResults> getGameResults();
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	Room& m_room;
};