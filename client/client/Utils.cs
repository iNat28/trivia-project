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
            windowToHide.Close();
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

        //Statistics
        STATISTICS = 30
    };

    //TODO: Add Keys for Json
    public static class Keys
    {

    }
}
