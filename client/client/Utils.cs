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
            windowToOpen.ShowDialog();
            LogoutWindow.toClose = true;
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

        //Statistics
        USER_STATS = 30,
        HIGH_SCORES
    };

    //TODO: Add Keys for Json
    public static class Keys
    {

    }
}
