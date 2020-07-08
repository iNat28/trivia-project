using Newtonsoft.Json.Linq;
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
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Window
    {
        //private readonly int roomId;
        //private static bool updateUserList;
        private readonly bool isAdmin;
        private readonly BackgroundWorker backgroundWorker;
        private readonly Mutex sendingMutex;
        private Status roomStatus = Status.OPEN;

        //TODO: Need to get room state instead of get players in room, and needs to check if the room closed or if the game started
        //Might want to do if(!isAdmin) before checking
        //TODO: Make sure all of the json keys are the same as in the back end

        public enum Status
        { 
            OPEN,
	        CLOSED,
	        GAME_STARTED
        };

        public Room(bool isAdmin, RoomData roomData)
        {
            InitializeComponent();
            User.errorOutput = this.errorOutput;
            sendingMutex = new Mutex();
            this.isAdmin = isAdmin;

            if (isAdmin)
                this.LeaveRoomButton.Visibility = Visibility.Hidden;
            else
            {
                this.CloseRoomButton.Visibility = Visibility.Hidden;
                this.StartGameButton.Visibility = Visibility.Hidden;
            }
            
            //TODO: add a thread here that updates this data when we add the functionality of changing these stats in the room window
            this.RoomName.Text = roomData.name;
            this.MaxPlayers.Text = roomData.maxPlayers.ToString();
            this.TimePerQuestion.Text = roomData.timePerQuestion.ToString();
            //adding users

            backgroundWorker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            backgroundWorker.DoWork += GetUsersList;
            backgroundWorker.ProgressChanged += ChangeWPF;
            backgroundWorker.RunWorkerCompleted += GetUsersCompleted;
            backgroundWorker.RunWorkerAsync();            
        }

        protected override void OnClosed(EventArgs e)
        {
            if (LogoutWindow.toClose)
            {
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
            backgroundWorker.CancelAsync();

            sendingMutex.WaitOne();
            Stream.Send(new JObject(), Codes.CLOSE_ROOM);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.CLOSE_ROOM))
            {
                Utils.OpenWindow(this, new MainWindow());
            }
        }

        private void LeaveRoom()
        {
            backgroundWorker.CancelAsync();

            sendingMutex.WaitOne();
            Stream.Send(new JObject(), Codes.LEAVE_ROOM);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.LEAVE_ROOM))
            {
                Utils.OpenWindow(this, new MainWindow());
            }
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {                     
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {
            backgroundWorker.CancelAsync();

            sendingMutex.WaitOne();
            Stream.Send(new JObject(), Codes.START_GAME);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.START_GAME))
            {
                Utils.OpenWindow(this, new Question(10, Convert.ToInt32(this.TimePerQuestion.Text)));
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
                Stream.Send(new JObject(), Codes.GET_ROOM_STATE);

                Response usersResponse = Stream.Recieve();

                backgroundWorker.ReportProgress(0, "");

                if (Stream.ResponseForThread(usersResponse, Codes.GET_ROOM_STATE, out string error))
                {
                    this.roomStatus = (Status)(int)usersResponse.jObject[Keys.roomStatus];
                    
                    if (this.roomStatus != Status.OPEN)
                    {
                        e.Cancel = true;
                        break;
                    }

                    JArray jArray = (JArray)usersResponse.jObject[Keys.players];

                    List<string> players = new List<string>();

                    foreach (JObject jObject in jArray)
                    {
                        string player = (string)jObject[Keys.username];
                        if(!this.NamesList.Items.Contains(player))
                        {
                            backgroundWorker.ReportProgress(1, player);
                        }
                        players.Add(player);
                    }
                    
                    for (int i = this.NamesList.Items.Count - 1; i >= 0; i--)
                    {
                        if (!players.Contains(this.NamesList.Items[i]))
                        {
                            backgroundWorker.ReportProgress(2, this.NamesList.Items[i].ToString());
                        }
                    }
                }
                else
                {
                    backgroundWorker.ReportProgress(3, error);
                }

                sendingMutex.ReleaseMutex();
                Thread.Sleep(3000);
            }
        }
        
        private void ChangeWPF(object sender, ProgressChangedEventArgs e)
        {
            string param = (string)e.UserState;
            switch (e.ProgressPercentage)
            {
                case 1:
                    this.NamesList.Items.Add(param);
                    break;
                case 2:
                    this.NamesList.Items.Remove(param);
                    break;
                case 3:
                    this.errorOutput.Text = param;
                    break;
            }
        }             

        private void GetUsersCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            Window newWindow = null;
            
            switch(roomStatus)
            {
                case Status.OPEN:
                    return;
                case Status.CLOSED:
                    newWindow = new MainWindow();
                    break;
                case Status.GAME_STARTED:
                    newWindow = new Question(10, Convert.ToInt32(this.TimePerQuestion.Text));
                    break;
            }

            Utils.OpenWindow(this, newWindow);
        }
    }
}
