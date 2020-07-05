using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace client
{
    public static class Utils
    {
        public static void OpenWindow(Window windowToHide, Window windowToOpen)
        {
            LogoutWindow.toClose = false;
            windowToHide.Close();
            LogoutWindow.toClose = true;
            windowToOpen.ShowDialog();
        }
    }

    public enum Codes
    {
        ERROR_CODE = 0,

	    //Login
	    LOGIN = 10,
	    SIGNUP,
	    LOGOUT,

	    //Room
	    GET_ROOM = 20,
	    GET_PLAYERS_IN_ROOM,
	    JOIN_ROOM,
	    CREATE_ROOM,
	    GET_ROOM_STATE,

	    //RoomAdmin
	    CLOSE_ROOM = 30,
	    START_GAME,

	    //RoomMember
	    LEAVE_ROOM = 40,

	    //Statistics
	    USER_STATS = 50,
	    HIGH_SCORES
    };

    public enum ResponseCodes
    {
        ERROR_RESPONSE,
	    SUCCESFUL
    };

    //TODO: Add Keys for Json
    public static class Keys
    {
        public const string username = "username";
        public const string password = "password";
        public const string email = "email";

        public const string roomId = "roomId";
        public const string roomName = "roomName";
        public const string questionCount = "questionCount";
        public const string answerTimeout = "answerTimeout";

        public const string userStats = "userStats";

        public const string status = "status";
        public const string message = "message";

        public const string rooms = "Rooms";
        public const string playersInRoom = "PlayersInRoom";
        public const string roomData = "roomData";
        public const string roomState = "roomState";

        public const string numPoints = "numPoints";
        public const string numTotalGames = "numTotalGames";
        public const string numCorrectAnswers = "numCorrectAnswers";
        public const string numWrongAnswers = "numWrongAnswers";
        public const string averageAnswerTime = "averageAnswerTime";
        public const string highScores = "highScores";

        public const string id = "id";
        public const string name = "name";
        public const string maxPlayers = "maxPlayers";
        public const string timePerQuestion = "timePerQuestion";
        public const string players = "players";
        public const string questionsCount = "questionsCount";
        public const string roomStatus = "roomStatus";

        public const string category = "category";
        public const string difficulty = "difficulty";
        public const string question = "question";
        public const string correctAnswer = "correctAnswer";
        public const string incorrectAnswer1 = "incorrectAnswer1";
        public const string incorrectAnswer2 = "incorrectAnswer2";
        public const string incorrectAnswer3 = "incorrectAnswer3";
    }
}
