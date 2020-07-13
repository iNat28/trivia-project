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
        public static string GetSecondsString(int time)
        {
            string ret = time + " second";

            if (time == 1)
            {
                return ret;
            }

            return ret + 's';
        }

        public static string GetSecondsString(double time)
        {
            return time.ToString("0.00") + " seconds";
        }
    }

    public enum Codes
    {
        ERROR_CODE = 0,

        //Login
        LOGIN = 10,
        SIGNUP,
        LOGOUT,


        //Menu
        GET_ROOM = 20,
        GET_PLAYERS_IN_ROOM,
        JOIN_ROOM,
        CREATE_ROOM,

        //Statistics
        USER_STATS,
        HIGH_SCORES,


        //Room
        GET_ROOM_STATE = 30,

        //RoomAdmin
        CLOSE_ROOM,
        START_GAME,

        //RoomMember
        LEAVE_ROOM,


        //Game
        GET_GAME_RESULTS,
        SUBMIT_ANSWER,
        GET_QUESTION,
        LEAVE_GAME
    };
    
    public static class Keys
    {
        /* Login */
        public const string username = "username";
        public const string password = "password";
        public const string email = "email";


        /* Rooms */

        //Requests
        public const string roomName = "roomName";
        public const string questionCount = "questionCount";
        public const string maxPlayers = "maxPlayers";
        public const string timePerQuestion = "timePerQuestion";
        public const string questionsCount = "questionsCount";

        //Responses
        public const string rooms = "rooms";
        public const string playersInRoom = "playersInRoom";
        public const string roomId = "roomId";
        public const string currentPlayerCount = "currentPlayerCount";
        public const string roomStatus = "roomStatus";


        /* Game */

        //Requests
        public const string answerIndex = "answerIndex";
        public const string answerTime = "answerTime";

        //Responses
        public const string category = "category";
        public const string difficulty = "difficulty";
        public const string question = "question";
        public const string answers = "answers";
        public const string correctAnswerIndex = "correctAnswerIndex";
        public const string playersResults = "playersResults";


        /* Statistics */
        public const string numPoints = "numPoints";
        public const string numTotalGames = "numTotalGames";
        public const string numCorrectAnswers = "numCorrectAnswers";
        public const string numWrongAnswers = "numWrongAnswers";
        public const string averageAnswerTime = "averageAnswerTime";
        public const string highScores = "highScores";

        /* Error Response */
        public const string message = "message";
    }
}
