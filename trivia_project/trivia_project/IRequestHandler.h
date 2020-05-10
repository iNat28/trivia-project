#pragma once
#include "pch.h"
#include "Constants.h"

interface IRequestHandler;

struct RequestInfo
{
	RequestInfo(RequestCodes RequestId, time_t receivalTime, Buffer buffer);
	RequestInfo();

	RequestCodes requestId;
	time_t receivalTime; 
	Buffer buffer;
};

struct RequestResult
{
	RequestResult(Buffer response, IRequestHandler* newHandler);
	RequestResult();

	Buffer response;
	IRequestHandler* newHandler;
};

interface IRequestHandler
{
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
	//static std::unordered_map<ResponseCodes, IRequestHandler*> responseCodesHandler;
};