#include "pch.h"
#include "Question.h"

void from_json(const json& j, Question& question)
{
	question = Question(
		j[Keys::category],
		j[Keys::difficulty],
		j[Keys::question],
		j[Keys::correctAnswer],
		std::array<string, 3>{
		j[Keys::incorrectAnswer1],
			j[Keys::incorrectAnswer2],
			j[Keys::incorrectAnswer3]
	}
	);
}

Question::Question(string category, string difficulty, string question, string correctAnswer, std::array<string, 3> incorrectAnswers) :
	category(category), difficulty(difficulty), question(question), correctAnswer(correctAnswer), incorrectAnswers(incorrectAnswers)
{
}

Question::Question()
{
}