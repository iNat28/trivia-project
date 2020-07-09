#pragma once
#include "pch.h"
#include "Codes.h"
#include "Requests.h"
#include "JsonResponsePacketSerializer.h"

class IRequestHandler;
typedef std::shared_ptr<IRequestHandler> IRequestHandlerPtr;

struct RequestInfo
{
	RequestInfo(Codes RequestId, time_t receivalTime, Buffer buffer);
	RequestInfo();

	Codes requestId;
	time_t receivalTime;
	Buffer buffer;
};

struct RequestResult
{
	RequestResult(Buffer response, IRequestHandler& newHandler);

	Buffer response;
	IRequestHandler& newHandler;
};

class IRequestHandler
{
public:
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
protected:
	template<typename Handler, typename Func>
	RequestResult handleAllRequests(const RequestInfo& requestInfo, Handler& handler, map<Codes, Func> requestMap)
	{
		Func requestFunc = nullptr;

		//If at any point the requests don't work, an exception will be thrown, 
		//and it will be put into an error response
		try {
			requestFunc = requestMap.at(requestInfo.requestId);
			return (handler.*requestFunc)(requestInfo);
		}
		//Exception caught
		catch (const std::exception & e)
		{
			return RequestResult(
				JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
				handler
			);
		}
	}
};