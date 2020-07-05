#pragma once

#include "pch.h"
#include "SqliteDataBase.h"

struct Question
{
	Question(string question, string correctAnswer, std::array<string, 3> incorrect_answers);
	string question;
	string correct_answer;
	std::array<string, 3> incorrect_answers;
};

struct GameData
{
	GameData(Question currentQuestion, int correctAnswerCount, int wrongAnswerCount, int averageAnswerTime);
	
	Question currentQuestion;
	int correctAnswerCount;
	int wrongAnswerCount;
	int averageAnswerTime;
};

class Game
{
public:
	Question getQuestionForUser(LoggedUser);
	bool submitAnswer(int answerChoice);
	void removePlayer(LoggedUser);

private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
};

