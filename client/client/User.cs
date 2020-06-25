﻿using System;
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
using Newtonsoft.Json.Linq;

namespace client
{
    class User
    {
        public static string username;
        public static TextBlock errorOutput;

        public static void PrintError(Exception e)
        {
            if (errorOutput != null)
            {
                errorOutput.Text = e.Message;
            }
            else
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}