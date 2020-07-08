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
	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			GetQuestionResponse(this->m_game.getQuestion())
		),
		this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game)
	);
}

RequestResult GameRequestHandler::_submitAnswer(const RequestInfo& requestInfo) const
{
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			SubmitAnswerResponse(this->m_game.submitAnswer(this->m_user, submitAnswerRequest.answerIndex, submitAnswerRequest.answerTime))
		),
		this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game)
	);
}

RequestResult GameRequestHandler::_getGameResults(const RequestInfo& requestInfo) const
{
	GetGameResultsResponse getGameResultsResponse(this->m_game.getGameResults(this->m_user));

	this->_deleteGameIfEmpty();

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(getGameResultsResponse),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	);
}

RequestResult GameRequestHandler::_leaveGame(const RequestInfo& requestInfo) const
{
	this->m_game.removePlayer(this->m_user);

	this->_deleteGameIfEmpty();

	return RequestResult(
		JsonResponsePacketSerializer::serializeResponse(
			LeaveRoomResponse()
		),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	);
}

void GameRequestHandler::_deleteGameIfEmpty() const
{
	if (this->m_game.allPlayersGotResults())
	{
		this->m_handlerFactory.getGameManager().deleteGame(this->m_game);
	}
}

const map<Codes, GameRequestHandler::requests_func_t> GameRequestHandler::m_requests = {
	{ Codes::GET_QUESTION, &GameRequestHandler::_getQuestion },
	{ Codes::SUBMIT_ANSWER, &GameRequestHandler::_submitAnswer },
	{ Codes::GET_GAME_RESULTS, &GameRequestHandler::_getGameResults },
	{ Codes::LEAVE_GAME, &GameRequestHandler::_leaveGame },
};
