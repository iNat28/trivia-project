#include "pch.h"
#include "IRequestHandler.h"

//std::unordered_map<ResponseCodes, IRequestHandler*> IRequestHandler::responseCodesHandler;

RequestInfo::RequestInfo(RequestCodes RequestId, time_t receivalTime, Buffer buffer) :
	requestId(RequestId), receivalTime(receivalTime), buffer(buffer)
{
}

RequestInfo::RequestInfo() :
	requestId(RequestCodes::ERROR_REQUEST), receivalTime(0), buffer()
{
}

RequestResult::RequestResult(Buffer response, IRequestHandler* newHandler) :
	response(response), newHandler(newHandler)
{
}

RequestResult::RequestResult() :
	response(), newHandler(nullptr)
{
}
