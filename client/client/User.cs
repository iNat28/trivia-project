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

        public static void PrintErrorAndClose(Exception e)
        {
            mutex.WaitOne();
            PrintError(e);
            Stream.Close();
            mutex.ReleaseMutex();
        }

        public static void PrintErrorAndKeep(Exception e)
        {
            mutex.WaitOne();
            PrintError(e);
            mutex.ReleaseMutex();
        }

        private static void PrintError(Exception e)
        {
            if(e is NullReferenceException || errorOutput == null)
            {
                Console.WriteLine(e.Message);
            }
            else
            {
                errorOutput.Text = e.Message;
            }
        }
    }
}
