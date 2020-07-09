using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace client
{
    public enum WindowTypes
    {
        LOGIN,
        SIGN_UP,
        MAIN,
        STATISTICS,
        MY_STATUS,
        HIGH_SCORE,
        CREATE_ROOM,
        JOIN_ROOM,
        ROOM,
        QUESTION,
        RESULT
    }

    public static class WindowManager
    {
        public static Dictionary<WindowTypes, CustomWindow> windows = new Dictionary<WindowTypes, CustomWindow>
        {
            { WindowTypes.LOGIN, new LoginWindow() },
            { WindowTypes.SIGN_UP, new SignUpWindow() },
            { WindowTypes.MAIN, new MainWindow() },
            { WindowTypes.STATISTICS, new StatisticsWindow() },
            { WindowTypes.MY_STATUS, new MyStatusWindow() },
            { WindowTypes.HIGH_SCORE, new HighScoreWindow() },
            { WindowTypes.CREATE_ROOM, new CreateRoomWindow() },
            { WindowTypes.JOIN_ROOM, new JoinRoomWindow() },
            { WindowTypes.ROOM, new RoomWindow() },
            { WindowTypes.QUESTION, new QuestionWindow() },
            { WindowTypes.RESULT, new ResultsWindow() }
        };

        public static bool exit = false;

        private static CustomWindow currentWindow;

        public static void OpenWindow(WindowTypes windowToOpen, params object[] param)
        {
            CustomWindow oldWindow = currentWindow;
            
            currentWindow = windows[windowToOpen];
            currentWindow.OnShow(param);
            
            if (currentWindow.ErrorBox != null)
            {
                currentWindow.ErrorBox.Text = "";
            }

            oldWindow.Hide();
            currentWindow.Show();
        }

        public static void Start()
        {
            currentWindow = windows[WindowTypes.LOGIN];
            currentWindow.OnShow();
            currentWindow.Show();
        }

        public static void Close()
        {
            WindowManager.exit = true;
            System.Windows.Application.Current.Shutdown();
        }

        public static void PrintError(string error)
        {
            if (currentWindow.ErrorBox == null)
            {
                Console.WriteLine(error);
            }
            else
            {
                currentWindow.ErrorBox.Text = error;
            }
        }

        public static void PrintError(Exception e)
        {
            PrintError(e.Message);
        }
    }
}
