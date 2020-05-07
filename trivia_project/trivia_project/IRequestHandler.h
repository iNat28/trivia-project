#pragma once
#include "pch.h"
#include "Constants.h"

interface IRequestHandler;

struct RequestInfo
{
	RequestCodes RequestId;
	time_t receivalTime; //TODO might need to change type
	Buffer buffer;
};

struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};

interface IRequestHandler
{
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};