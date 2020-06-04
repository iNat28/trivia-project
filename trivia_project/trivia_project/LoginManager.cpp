#include "pch.h"
#include "LoginManager.h"

LoginManager::LoginManager(IDatabase& database) :
	m_database(database)
{
}

void LoginManager::signup(string username, string password, string email)
{
	if (this->m_database.doesUserExist(username))
	{
		throw Exception("User already signed up");
	}

	//Adds the user
	this->m_database.addNewUser(username, password, email);
	this->m_loggedUsers.push_back(username);
}

void LoginManager::login(string username, string password)
{
	if (!this->m_database.doesUserExist(username))
	{
		throw Exception("User not signed up");
	}

	for (const auto& loggedUser : this->m_loggedUsers)
	{
		if (loggedUser.m_username == username)
		{
			throw Exception("User already logged in");
		}
	}
	
	//Logins in the user
	this->m_loggedUsers.push_back(username);
}

void LoginManager::logout(string username)
{
	for (auto loggedUser = this->m_loggedUsers.begin(); loggedUser != this->m_loggedUsers.end(); loggedUser++)
	{
		if (loggedUser->m_username == username)
		{
			this->m_loggedUsers.erase(loggedUser);
		}
	}
}

