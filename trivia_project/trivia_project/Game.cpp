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

//TODO: Store in DB as int not string
unsigned int Question::getDifficulty() const
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

Game::Game(Room& room, std::queue<Question> questions) : 
	m_room(room), m_questions(questions)
{
	for (const auto& player : m_room.getAllUsers())
	{
		this->m_players[player];
	}
}

Game::Game() : 
	m_room(*std::make_shared<Room>())
{
}

const Question& Game::getQuestion() const
{
	if (this->m_questions.empty())
	{
		throw Exception("Couldn't get question - no questions left!");
	}
	return this->m_questions.front();
}

unsigned int Game::submitAnswer(LoggedUser user, unsigned int answerIndex, unsigned int answerTime)
{
	PlayerResults& playerResults = this->m_players[user].playerResults;
	const Question& question = this->getQuestion();
	
	if (answerTime < 1 || answerTime > MAX_ANSWER_TIME)
	{
		throw Exception("Invalid answer time!");
	}

	playerResults.averageAnswerTime = 
		(playerResults.averageAnswerTime * playerResults.totalNumAnswers() + answerTime) / (playerResults.totalNumAnswers() + 1);
	if (question.correctAnswerIndex == answerIndex)
	{
		playerResults.numCorrectAnswers++;
		playerResults.numPoints += question.getDifficulty() * (MAX_ANSWER_TIME - answerTime) * POINT_MULTIPLIER;
	}
	else
	{
		playerResults.numWrongAnswers++;
	}

	this->m_questions.pop();
	return 0;
}

PlayerResults Game::removePlayer(LoggedUser user)
{
	PlayerResults playerResults = this->m_players.at(user).playerResults;

	this->m_players.erase(user);

	return playerResults;
}

//TODO: Change to struct, or change to find a different solution
//Returns the players results, and if all of the users received the game results
std::pair<map<LoggedUser, PlayerResults>, bool> Game::getGameResults(LoggedUser user)
{
	if (!this->m_questions.empty())
	{
		throw Exception("The game isn't over!");
	}

	map<LoggedUser, PlayerResults> playersResults;
	bool gotResults = true;

	this->m_players[user].gotData = true;

	//Converts the map so the value will be PlayerResults and not GameData
	for (const auto& player : this->m_players)
	{
		playersResults[player.first] = player.second.playerResults;
		gotResults = gotResults && player.second.gotData;
	}

	return { playersResults, gotResults };
}

bool Game::empty() const
{
	return this->m_players.empty();
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
