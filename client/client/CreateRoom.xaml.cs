﻿using Newtonsoft.Json.Linq;
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

namespace client
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public CreateRoom()
        {
            InitializeComponent();
        }
        //unsigned int id;
        //string name;
        //unsigned int maxPlayers;
        //unsigned int timePerQuestion;
        //unsigned int isActive;
        //unsigned int numQuestionsAsked;
        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (!(this.RoomName.Text == "") && !(this.MaxPlayers.Text == "") && !(this.AnswerTime.Text == ""))
            {

                JObject jObject = new JObject
                {
                    ["roomId"] = 0,
                    ["roomName"] = this.RoomName.Text,
                    ["maxPlayers"] = Convert.ToInt32(this.MaxPlayers.Text),
                    ["isActive"] = false,
                    ["numQuestionsAsked"] = 0
                };
                
                Stream.Send(jObject, Codes.CREATE_ROOM);

                Response response = Stream.Recieve();

                if (Stream.Response(response, Codes.CREATE_ROOM, this.ErrorBox))
                    Utils.OpenWindow(this, new Room(true, this.RoomName.Text, Convert.ToInt32(this.MaxPlayers.Text), Convert.ToInt32(this.AnswerTime.Text)));
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
