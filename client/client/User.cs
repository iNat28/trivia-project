using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Threading;
using Newtonsoft.Json.Linq;

namespace client
{
    class User
    {
        public static string username;
        public static TextBlock errorOutput;
        public static Mutex mutex = new Mutex();
        public static Window currentWindow;

        public static void PrintError(string error)
        {
            //In case there are multiple errors to be printed
            mutex.WaitOne();
            if (errorOutput == null)
            {
                Console.WriteLine(error);
            }
            else
            {
                errorOutput.Text = error;
            }
            mutex.ReleaseMutex();
        }

        public static void PrintError(Exception e)
        {
            User.PrintError(e.Message);
        }
    }
}
