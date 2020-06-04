#include "pch.h"
#include "Requests.h"

LoginRequest::LoginRequest(string username, string password) : 
	username(username), password(password)
{
}

SignupRequest::SignupRequest(string username, string password, string email) :
	email(email), LoginRequest(username, password)
{
}

RoomIdRequest::RoomIdRequest(unsigned int roomId) :
	roomId(roomId)
{
}

CreateRoomRequest::CreateRoomRequest(string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout) : 
	roomName(roomName), maxUsers(maxUsers), questionCount(questionCount), answerTimeout(answerTimeout)
{
}
