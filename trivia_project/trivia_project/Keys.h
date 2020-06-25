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
	static const char* maxUsers;
	static const char* questionCount;
	static const char* answerTimeout;
	
	//Statistics
	static const char* userStats;
	
	/* Responses */

	static const char* message;
	static const char* status;

	//Rooms
	static const char* rooms;
	static const char* playersInRoom;

	//Statistics
	static const char* numPoints;
	static const char* numTotalGames;
	static const char* numCorrectAnswers;
	static const char* numWrongAnswers;
	static const char* averageAnswerTime;

	/* Objects */

	//RoomData
	static const char* id;
	static const char* name;
	static const char* maxPlayers;
	static const char* timePerQuestion;
	static const char* isActive;
	static const char* users;
	static const char* numQuestionsAsked;

	//Question
	static const char* category;
	static const char* difficulty;
	static const char* question;
	static const char* correctAnswer;
	static const char* incorrectAnswer1;
	static const char* incorrectAnswer2;
	static const char* incorrectAnswer3;
};