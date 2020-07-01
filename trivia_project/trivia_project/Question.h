#pragma once
#include "pch.h"
#include "Keys.h"

struct Question
{
	Question(string category, string difficulty, string question, string correctAnswer, std::array<string, 3> incorrectAnswers);
	Question();

	string category;
	string difficulty;
	string question;
	string correctAnswer;
	std::array<string, 3> incorrectAnswers;
};

void from_json(const json& j, Question& question);