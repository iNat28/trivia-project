#pragma once
#include "IRequestHandler.h"

class RoomMemberRequestHandler :
	public IRequestHandler
{
public:
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const;
private:

};

