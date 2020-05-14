#pragma once
#include <iostream>

using std::string;

class LoggedUser
{
public:
	LoggedUser(string username);

	string getUsername() const;
private:
	string m_username;
};

