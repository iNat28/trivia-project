#pragma once
#include "LoggedUserRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler :
	public LoggedUserRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Game& game);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const override;
private:
	RequestHandlerFactory& m_handlerFactory;
	using requests_func_t = RequestResult(GameRequestHandler::*)(const RequestInfo&) const;
	static const map<Codes, GameRequestHandler::requests_func_t> m_requests;
	Game& m_game;

	RequestResult _getQuestion(const RequestInfo& requestInfo) const;
	RequestResult _submitAnswer(const RequestInfo& requestInfo) const;
	RequestResult _getGameResults(const RequestInfo& requestInfo) const;
	RequestResult _leaveGame(const RequestInfo& requestInfo) const;
};

