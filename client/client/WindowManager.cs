using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Animation;

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

        private static readonly DoubleAnimation fadeIn = new DoubleAnimation(0, 1, new Duration(TimeSpan.FromMilliseconds(250)));

        public static bool exit = false;

        private static CustomWindow currentWindow;

        public static void OpenWindow(WindowTypes windowToOpen, params object[] param)
        {
            CustomWindow oldWindow = currentWindow;

            currentWindow = windows[windowToOpen];
            currentWindow.Height = oldWindow.Height;
            currentWindow.Width = oldWindow.Width;
            currentWindow.GetErrorOutput().Text = "";
            currentWindow.OnShow(param);

            currentWindow.Top = oldWindow.Top;
            currentWindow.Left = oldWindow.Left;
            
            oldWindow.Hide();
            currentWindow.Show();
            
            currentWindow.Top = oldWindow.Top;
            currentWindow.Left = oldWindow.Left;
            
            currentWindow.BeginAnimation(UIElement.OpacityProperty, WindowManager.fadeIn);
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
            currentWindow.GetErrorOutput().Text = error;
        }
    }
}
