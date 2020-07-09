#pragma once
#include "LoggedUserRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler :
	public LoggedUserRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

	void reset(LoggedUser user, Game& game);
private:
	RequestHandlerFactory& m_handlerFactory;
	using requests_func_t = RequestResult(GameRequestHandler::*)(const RequestInfo&);
	static const map<Codes, GameRequestHandler::requests_func_t> m_requests;
	Game* m_game;

	RequestResult _getQuestion(const RequestInfo& requestInfo);
	RequestResult _submitAnswer(const RequestInfo& requestInfo);
	RequestResult _getGameResults(const RequestInfo& requestInfo);
	RequestResult _leaveGame(const RequestInfo& requestInfo);
	void _deleteGameIfEmpty() const;
};

