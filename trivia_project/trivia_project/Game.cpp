#include "pch.h"
#include "Game.h"

Question Game::getQuestionForUser(LoggedUser)
{
	return Question();
}

bool Game::submitAnswer(int answerChoice)
{
	return false;
}

void Game::removePlayer(LoggedUser)
{
}
