#pragma once
#include "IRequestHandler.h"

class RoomAdminRequestHandler :
	public IRequestHandler
{
public:
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const;
private:

};

