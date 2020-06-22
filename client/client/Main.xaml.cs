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
    /// <summary>
    /// Interaction logic for Main.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly string username;

        public MainWindow(string username)
        {
            this.username = username;
            InitializeComponent();
            UsernameHeader.Text += this.username;
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            JObject jObject = new JObject
            {
                ["username"] = username
            };
            Stream.Send(jObject, Codes.LOGOUT);
            Stream.Close();
        }

        private void SignoutButton_Click(object sender, RoutedEventArgs e)
        {
            JObject jObject = new JObject
            {
                ["username"] = username
            };
            Stream.Send(jObject, Codes.LOGOUT);
            Utils.OpenWindow(this, new LoginWindow());
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void StatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new Statistics(this.username));
        }
    }
}
