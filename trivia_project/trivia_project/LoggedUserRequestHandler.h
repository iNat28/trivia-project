#pragma once
#include "IRequestHandler.h"

class LoggedUserRequestHandler :
	public IRequestHandler
{
protected:
	LoggedUser m_user;
};

