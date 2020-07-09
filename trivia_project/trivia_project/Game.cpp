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
	m_room(room)
{
	for (const auto& player : m_room.getAllUsers())
	{
		this->m_players[player];
		this->m_questions[player] = questions;
	}
}

Game::Game() : 
	m_room(*std::make_shared<Room>())
{
}

const Question& Game::getQuestion(LoggedUser user) const
{
	if (this->m_questions.empty())
	{
		throw Exception("Couldn't get question - no questions left!");
	}
	return this->m_questions.at(user).back();
}

unsigned int Game::submitAnswer(LoggedUser user, int answerIndex, int answerTime)
{
	PlayerResults& playerResults = this->m_players[user].playerResults;
	const Question& question = this->getQuestion(user);

	playerResults.averageAnswerTime = 
		(playerResults.averageAnswerTime * playerResults.totalNumAnswers() + answerTime) / 
		(float)(playerResults.totalNumAnswers() + 1);
	if (question.correctAnswerIndex == answerIndex)
	{
		playerResults.numCorrectAnswers++;
		playerResults.numPoints += question.difficulty * (MAX_ANSWER_TIME + 1 - answerTime) * POINT_MULTIPLIER;
	}
	else
	{
		playerResults.numWrongAnswers++;
	}

	this->m_questions[user].pop_back();
	return question.correctAnswerIndex;
}

void Game::removePlayer(LoggedUser user)
{
	this->m_players[user].gotResults = true;
}

//Returns the players results, and if all of the users received the game results
vector<UserResults> Game::getGameResults(LoggedUser user)
{
	if (!this->m_questions[user].empty())
	{
		throw Exception("The game isn't over!");
	}

	this->m_players[user].gotResults = true;

	return this->getGameResults();
}

vector<UserResults> Game::getGameResults()
{
	vector<UserResults> playersResults;
	
	//Converts the map so the value will be PlayerResults and not GameData
	for (const auto& player : this->m_players)
	{
		playersResults.push_back(UserResults(player.first, player.second.playerResults));
	}

	std::sort(playersResults.begin(), playersResults.end(), comaprePlayerPoints);

	return playersResults;
}

bool comaprePlayerPoints(UserResults i1, UserResults i2)
{
	return (i1.playerResults.numPoints > i2.playerResults.numPoints);
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

GameData::GameData(PlayerResults playerResults, bool gotResults) : 
	playerResults(playerResults), gotResults(gotResults)
{
}

GameData::GameData() : 
	playerResults(), gotResults(false)
{
}
