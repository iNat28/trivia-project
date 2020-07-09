#include "pch.h"
#include "IRequestHandler.h"

RequestInfo::RequestInfo(Codes RequestId, time_t receivalTime, Buffer buffer) :
	requestId(RequestId), receivalTime(receivalTime), buffer(buffer)
{
}

RequestInfo::RequestInfo() :
	requestId(Codes::ERROR_CODE), receivalTime(0)
{
}

RequestResult::RequestResult(Buffer response, IRequestHandler& newHandler) :
	response(response), newHandler(newHandler)
{
}