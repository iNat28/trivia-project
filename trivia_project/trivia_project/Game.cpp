#include "pch.h"
#include "Game.h"

Question::Question(string category, unsigned int difficulty, string question, vector<string> answers, unsigned int correctAnswerIndex) :
	category(category), difficulty(difficulty), question(question), answers(answers), correctAnswerIndex(correctAnswerIndex)
{
}

Question::Question() :
	correctAnswerIndex(0), difficulty(1)
{
}

unsigned int Question::getDifficulty(string difficulty)
{
	if (difficulty == "easy")
	{
		return 1;
	}
	if (difficulty == "medium")
	{
		return 2;
	}
	return 3; //hard
}

void to_json(json& j, const Question& question)
{
	j[Keys::category] = question.category;
	j[Keys::difficulty] = question.difficulty;
	j[Keys::question] = question.question;
	j[Keys::answers] = question.answers;
}

void from_json(const json& j, Question& question)
{
	question = Question(
		j[Keys::category],
		Question::getDifficulty(j[Keys::difficulty]),
		j[Keys::question],
		j["incorrect_answers"],
		3
	);

	while (question.answers.size() < 3)
	{
		question.answers.push_back("");
	}

	question.answers.push_back(j["correct_answer"]);
}

Game::Game(Room& room, Questions questions) :
	m_room(room), m_questions(questions)
{
	for (const auto player : this->m_room.getAllUsers())
	{
		this->m_players[player.username];
	}
}

const Question& Game::getQuestion(LoggedUser& user) const
{
	if (this->m_questions.empty())
	{
		throw Exception("Couldn't get question - no questions left!");
	}
	return this->m_questions[this->m_players.at(user.username).currentQuestionIndex];
}

unsigned int Game::submitAnswer(LoggedUser& user, int answerIndex, double answerTime)
{
	GameData& gameData = this->m_players[user.username];
	const Question& question = this->getQuestion(user);

	gameData.playerResults.averageAnswerTime =
		(gameData.playerResults.averageAnswerTime * gameData.playerResults.totalNumAnswers() + answerTime) /
		(gameData.playerResults.totalNumAnswers() + 1.0);
	if (question.correctAnswerIndex == answerIndex)
	{
		gameData.playerResults.numCorrectAnswers++;
		gameData.playerResults.numPoints += (unsigned int)(question.difficulty * (MAX_ANSWER_TIME + 1.0 - answerTime) * POINT_MULTIPLIER);
	}
	else
	{
		gameData.playerResults.numWrongAnswers++;
	}

	gameData.currentQuestionIndex++;
	return question.correctAnswerIndex;
}

void Game::removePlayer(LoggedUser& user)
{
	this->m_players[user.username].gotResults = true;
}

bool Game::comparePlayerPoints(UserResults userResults1, UserResults userResults2)
{
	return (userResults1.playerResults.numPoints > userResults2.playerResults.numPoints);
}

//Makes sure to check that the game isn't over
vector<UserResults> Game::getGameResults(LoggedUser& user)
{
	if (this->m_players.at(user.username).currentQuestionIndex < this->m_questions.size())
	{
		throw Exception("The game isn't over!");
	}

	return this->getGameResults();
}

vector<UserResults> Game::getGameResults()
{
	vector<UserResults> playersResults;

	//Converts the map so the value will be PlayerResults and not GameData
	for (const auto player : this->m_players)
	{
		playersResults.push_back(UserResults(player.first, player.second.playerResults));
	}

	std::sort(playersResults.begin(), playersResults.end(), comparePlayerPoints);

	return playersResults;
}

Room& Game::getRoom()
{
	return this->m_room;
}

bool Game::allPlayersGotResults() const
{
	for (const auto& player : this->m_players)
	{
		if (!player.second.gotResults)
		{
			return false;
		}
	}

	return true;
}

bool Game::operator==(const Game& other) const
{
	return this->m_room.getId() == other.m_room.getId();
}

bool Game::operator==(const Room& other) const
{
	return this->m_room.getId() == other.getId();
}

Game& Game::operator=(const Game& other)
{
	this->m_players = other.m_players;
	this->m_questions = other.m_questions;
	std::cout << "Copied game" << std::endl;
	return *this;
}

GameData::GameData(PlayerResults playerResults, bool gotResults, unsigned int currentQuestionIndex) :
	playerResults(playerResults), gotResults(gotResults), currentQuestionIndex(currentQuestionIndex)
{
}

GameData::GameData() :
	playerResults(), gotResults(false), currentQuestionIndex(0)
{
}
