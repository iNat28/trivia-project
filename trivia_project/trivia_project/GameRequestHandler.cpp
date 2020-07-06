#include "pch.h"
#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user, Game& game) : 
	LoggedUserRequestHandler(user), m_handlerFactory(handlerFactory), m_game(game)
{
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	GameRequestHandler::requests_func_t handler = nullptr;

	//If at any point the requests don't work, an exception will be thrown, 
	//and it will be put into an error response
	try {
		handler = m_requests.at(requestInfo.requestId);
		return (this->*handler)(requestInfo);
	}
	catch (const std::exception & e)
	{
		return RequestResult(
			JsonResponsePacketSerializer::serializeResponse(ErrorResponse(e.what())),
			this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game)
		);
	}
}

RequestResult GameRequestHandler::_getQuestion(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

RequestResult GameRequestHandler::_submitAnswer(const RequestInfo& requestInfo) const
{
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			SubmitAnswerResponse(this->m_game.submitAnswer(this->m_user, submitAnswerRequest.answerIndex))
		),
		this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game)
	);
}

RequestResult GameRequestHandler::_getGameResults(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

RequestResult GameRequestHandler::_leaveGame(const RequestInfo& requestInfo) const
{
	return RequestResult();
}

const map<Codes, GameRequestHandler::requests_func_t> GameRequestHandler::m_requests = {
	{ Codes::GET_QUESTION, &GameRequestHandler::_getQuestion }
};
