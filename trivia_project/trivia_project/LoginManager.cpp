#include "pch.h"
#include "LoginManager.h"

LoginManager::LoginManager(IDatabasePtr database) :
	m_database(database)
{
}

void LoginManager::signup(string username, string password, string email)
{
	this->m_database->addNewUser(username, password, email);
	LoggedUser user(username);
	this->m_loggedUsers.push_back(user);
}

void LoginManager::login(string username, string password)
{
	this->m_database->doesPasswordMatch(username, password);
	LoggedUser user(username);
	this->m_loggedUsers.push_back(user);
}

void LoginManager::logout(string username)
{
	vector<LoggedUser>::iterator it;
	for (it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == username)
			this->m_loggedUsers.erase(it);
	}
}

