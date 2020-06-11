#pragma once
#include "pch.h"
#include "Keys.h"

struct LoggedUser
{
	LoggedUser(string username);
	LoggedUser();

	string username;
	int numCorrectAnswers;
	int answerTime;
	int numPoints;
};

void to_json(json& j, const LoggedUser& loggedUser);