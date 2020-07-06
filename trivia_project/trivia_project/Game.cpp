#include "pch.h"
#include "Game.h"

Question::Question(string category, string difficulty, string question, std::array<string, 4> answers, unsigned int correctAnswerIndex) :
	category(category), difficulty(difficulty), question(question), answers(answers), correctAnswerIndex(correctAnswerIndex)
{
}

Question::Question() :
	correctAnswerIndex(0)
{
}

void to_json(json& j, const Question& question)
{
	j[Keys::category] = question.category;
	j[Keys::difficulty] = question.difficulty;
	j[Keys::question] = question.question;
	j[Keys::answers] = question.answers;
}

//TODO: Fix when reading from file
void from_json(const json& j, Question& question)
{
	question = Question(
		j[Keys::category],
		j[Keys::difficulty],
		j[Keys::question],
		j[Keys::answers],
		j[Keys::correctAnswerIndex]
	);
}

Game::Game(Room& room) : 
	m_room(room)
{
	//TODO: Get the questions
	//TODO: Get the users
}

Question Game::getQuestionForUser(LoggedUser)
{
	return Question();
}

unsigned int Game::submitAnswer(LoggedUser user, unsigned int answerChoice)
{
	return 0;
}

void Game::removePlayer(LoggedUser)
{
}

vector<PlayerResults> Game::getGameResults()
{
	return vector<PlayerResults>();
}

GameData::GameData(Question currentQuestion, PlayerResults playerResults) : 
	currentQuestion(currentQuestion), playerResults(playerResults)
{
}
