﻿using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
    public enum RoomStatus
    {
        OPEN,
        CLOSED,
        GAME_STARTED
    };

    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class RoomWindow : CustomWindow
    {
        private bool isAdmin;
        private readonly BackgroundWorker backgroundWorker;
        private int questionsCount;
        private int timePerQuestion;
        private Mutex sendingMutex;
        private RoomStatus roomStatus;
        
        private enum ThreadCodes
        {
            ADD_PLAYER,
            REMOVE_PLAYER,
            PRINT_ERROR
        }

        public RoomWindow()
        {
            InitializeComponent();

            this.roomStatus = RoomStatus.OPEN;

            //adding users
            backgroundWorker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            backgroundWorker.DoWork += GetUsersList;
            backgroundWorker.ProgressChanged += ChangeWPF;
            backgroundWorker.RunWorkerCompleted += GetUsersCompleted;
        }

        protected override Border GetBorder()
        {
            return this.Border;
        }

        public override void OnShow(params object[] param)
        {
            this.isAdmin = (bool)param[0];
            RoomData roomData = (RoomData)param[1];

            this.roomStatus = RoomStatus.OPEN;
            sendingMutex?.Close();
            sendingMutex = new Mutex();

            if (isAdmin)
            {
                this.LeaveRoomButton.Visibility = Visibility.Hidden;
                this.CloseRoomButton.Visibility = Visibility.Visible;
                this.StartGameButton.Visibility = Visibility.Visible;
            }
            else
            {
                this.LeaveRoomButton.Visibility = Visibility.Visible;
                this.CloseRoomButton.Visibility = Visibility.Hidden;
                this.StartGameButton.Visibility = Visibility.Hidden;
            }

            this.questionsCount = roomData.questionsCount;
            this.timePerQuestion = roomData.timePerQuestion;

            this.RoomDetails.Text =
                "Room name: " + roomData.name + '\n' +
                Utils.GetProperString(roomData.questionsCount, "question") + 
                "\nMax players: " + roomData.maxPlayers + '\n' +
                Utils.GetProperString(roomData.timePerQuestion, "second") + " per question\n";
            this.NamesList.Items.Clear();

            backgroundWorker.RunWorkerAsync();
        }

        public override TextBlock GetErrorOutput()
        {
            return this.ErrorOutput;
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            if (!WindowManager.exit)
            {
                base.OnClosing(e);
                if (isAdmin)
                {
                    CloseRoom();
                }
                else
                {
                    LeaveRoom();
                }
            }
        }

        private void CloseRoom()
        {
            sendingMutex.WaitOne();
            Response response = Stream.Send(Codes.CLOSE_ROOM);

            if (Stream.Response(response, Codes.CLOSE_ROOM))
            {
                backgroundWorker.CancelAsync();

                WindowManager.OpenWindow(WindowTypes.MAIN);
            }
        }

        private void LeaveRoom()
        {
            sendingMutex.WaitOne();
            Response response = Stream.Send(Codes.LEAVE_ROOM);

            if (Stream.Response(response, Codes.LEAVE_ROOM))
            {
                backgroundWorker.CancelAsync();

                WindowManager.OpenWindow(WindowTypes.MAIN);
            }
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {                     
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {
            sendingMutex.WaitOne();
            Response response = Stream.Send(Codes.START_GAME);

            if (Stream.Response(response, Codes.START_GAME))
            {
                backgroundWorker.CancelAsync();

                this.ShowQuestionWindow();
            }
        }

        private void CloseRoomButton_Click(object sender, RoutedEventArgs e)
        {
            CloseRoom();
        }

        private void LeaveGameButton_Click(object sender, RoutedEventArgs e)
        {
            LeaveRoom();
        }

        private void GetUsersList(object sender, DoWorkEventArgs e)
        {
            while (true)
            {                
                if(backgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                sendingMutex.WaitOne();
                Response usersResponse = Stream.Send(Codes.GET_ROOM_STATE, false);

                if (Stream.ResponseForThread(usersResponse, Codes.GET_ROOM_STATE, out string error))
                {
                    this.roomStatus = (RoomStatus)(int)usersResponse.jObject[Keys.roomStatus];
                    
                    if (this.roomStatus != RoomStatus.OPEN)
                    {
                        e.Cancel = true;
                        break;
                    }

                    JArray jArray = (JArray)usersResponse.jObject[Keys.playersInRoom];

                    List<string> players = new List<string>();

                    foreach (JObject jObject in jArray)
                    {
                        string player = (string)jObject[Keys.username];
                        if(!this.NamesList.Items.Contains(player))
                        {
                            backgroundWorker.ReportProgress((int)ThreadCodes.ADD_PLAYER, player);
                        }
                        players.Add(player);
                    }
                    
                    for (int i = this.NamesList.Items.Count - 1; i >= 0; i--)
                    {
                        if (!players.Contains(this.NamesList.Items[i]))
                        {
                            backgroundWorker.ReportProgress((int)ThreadCodes.REMOVE_PLAYER, this.NamesList.Items[i].ToString());
                        }
                    }
                }
                else
                {
                    if (Stream.backendClosed)
                    {
                        e.Cancel = true;
                        break;
                    }
                    backgroundWorker.ReportProgress((int)ThreadCodes.PRINT_ERROR, error);
                }

                sendingMutex.ReleaseMutex();
                Thread.Sleep(500);
            }
        }
        
        private void ChangeWPF(object sender, ProgressChangedEventArgs e)
        {
            string param = (string)e.UserState;
            switch ((ThreadCodes)e.ProgressPercentage)
            {
                case ThreadCodes.ADD_PLAYER:
                    this.NamesList.Items.Add(param);
                    break;
                case ThreadCodes.REMOVE_PLAYER:
                    this.NamesList.Items.Remove(param);
                    break;
                case ThreadCodes.PRINT_ERROR:
                    this.ErrorOutput.Text = param;
                    break;
            }
        }             

        private void GetUsersCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if(Stream.backendClosed)
            {
                Stream.Close();
                return;
            }

            switch(roomStatus)
            {
                case RoomStatus.OPEN:
                    return;
                case RoomStatus.CLOSED:
                    WindowManager.OpenWindow(WindowTypes.MAIN);
                    WindowManager.PrintError("Room closed");
                    break;
                case RoomStatus.GAME_STARTED:
                    this.ShowQuestionWindow();
                    break;
                default:
                    throw new IndexOutOfRangeException();
            }
        }

        private void ShowQuestionWindow()
        {
            WindowManager.OpenWindow(WindowTypes.QUESTION, this.questionsCount, this.timePerQuestion);
        }
    }
}
