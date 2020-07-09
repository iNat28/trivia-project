#pragma once

struct Keys
{
	/* Responses */
	
	//Login
	static const char* username;
	static const char* password;
	static const char* email;
	
	//Rooms
	static const char* roomId;
	static const char* roomName;
	static const char* questionCount;
	static const char* answerTimeout;
	
	//Statistics
	static const char* userStats;
	
	//Game
	static const char* answerIndex;
	static const char* answerTime;
	static const char* playersResults;

	/* Responses */

	static const char* message;
	static const char* status;

	//Rooms
	static const char* rooms;
	static const char* playersInRoom;
	static const char* roomState;
	static const char* roomData;

	//Statistics
	static const char* numPoints;
	static const char* numTotalGames;
	static const char* numCorrectAnswers;
	static const char* numWrongAnswers;
	static const char* averageAnswerTime;
	static const char* highScores;

	/* Objects */

	//Room
	static const char* id;
	static const char* name;
	static const char* maxPlayers;
	static const char* timePerQuestion;
	static const char* roomStatus;
	static const char* players;
	static const char* questionsCount;

	//Question
	static const char* category;
	static const char* difficulty;
	static const char* question;
	static const char* answers;
	static const char* correctAnswerIndex;
};