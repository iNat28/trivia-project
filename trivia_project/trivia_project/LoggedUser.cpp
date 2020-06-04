#include "pch.h"
#include "LoggedUser.h"

LoggedUser::LoggedUser(string username) : 
	m_username(username)
{
}

string LoggedUser::getUsername() const
{
	return this->m_username;
}
