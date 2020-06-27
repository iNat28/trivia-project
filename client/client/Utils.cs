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
            User.errorOutput = null;
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
        CLOSE_ROOM,

        //Statistics
        USER_STATS = 30,
        HIGH_SCORES
    };

    //TODO: Add Keys for Json
    public static class Keys
    {
        public const string username = "username";
        public const string password = "password";
        public const string email = "email";

        public const string roomId = "roomId";
        public const string roomName = "roomName";
        public const string maxUsers = "maxUsers";
        public const string questionCount = "questionCount";
        public const string answerTimeout = "answerTimeout";

        public const string userStats = "userStats";

        public const string status = "status";
        public const string message = "message";

        public const string rooms = "Rooms";
        public const string playersInRoom = "PlayersInRoom";

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
        public const string isActive = "isActive";
        public const string users = "users";
        public const string numQuestionsAsked = "numQuestionsAsked";

        public const string category = "category";
        public const string difficulty = "difficulty";
        public const string question = "question";
        public const string correctAnswer = "correctAnswer";
        public const string incorrectAnswer1 = "incorrectAnswer1";
        public const string incorrectAnswer2 = "incorrectAnswer2";
        public const string incorrectAnswer3 = "incorrectAnswer3";
    }
}
