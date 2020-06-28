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
    public partial class Room : LogoutWindow
    {
        private readonly int roomId;
        //private static bool updateUserList;
        private bool isAdmin;
        private BackgroundWorker backgroundWorker;
        private Mutex sendingMutex;
        private bool close = false;
        
        public Room(bool isAdmin, string roomName, int maxPlayers, int answerTime)
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
            //getting id of room
            Stream.Send(new JObject(), Codes.GET_ROOM);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.GET_ROOM))
            {
                JArray jArray = (JArray)response.jObject[Keys.rooms];
                foreach (JObject jObject in jArray)
                {
                    if (jObject[Keys.name].ToString() == roomName)
                        this.roomId = Convert.ToInt32(jObject[Keys.id].ToString());
                }
            }
            //adding users

            backgroundWorker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            backgroundWorker.DoWork += GetUsersList;
            backgroundWorker.ProgressChanged += AddUserToList;
            backgroundWorker.RunWorkerCompleted += GetUsersCompleted;
            backgroundWorker.RunWorkerAsync();
        }

        protected override void OnClosed(EventArgs e)
        {
            OnClosedBase(e);

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
            JObject jObject = new JObject
            {
                ["roomId"] = roomId
            };
            Stream.Send(jObject, Codes.CLOSE_ROOM);

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
            JObject jObject = new JObject
            {
                ["roomId"] = roomId
            };
            Stream.Send(jObject, Codes.LEAVE_ROOM);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.LEAVE_ROOM))
            {
                Utils.OpenWindow(this, new MainWindow());
            }
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //get list of usernames in the room and add then to the list like this:
            
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {
            //starts game
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
                JObject roomIdJObject = new JObject
                {
                    ["roomId"] = roomId
                };
                Stream.Send(roomIdJObject, Codes.GET_PLAYERS_IN_ROOM);

                Response usersResponse = Stream.Recieve();

                //If the room is closed
                //TODO: Change code to be room is closed
                if(usersResponse.code == Codes.ERROR_CODE)
                {
                    e.Cancel = true;
                    close = true;
                    break;
                }
                if (Stream.Response(usersResponse, Codes.GET_PLAYERS_IN_ROOM))
                {
                    JArray jArray = (JArray)usersResponse.jObject[Keys.playersInRoom];
                    foreach (JObject jObject in jArray)
                    {
                        Console.WriteLine((string)jObject[Keys.username]);
                        backgroundWorker.ReportProgress(0, (string)jObject[Keys.username]);
                    }
                }

                sendingMutex.ReleaseMutex();
                Thread.Sleep(3000);
            }
        }

        private void AddUserToList(object sender, ProgressChangedEventArgs e)
        {
            if (!this.NamesList.Items.Contains(e.UserState))
            {
                this.NamesList.Items.Add(e.UserState);
            }
        }

        private void GetUsersCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if(close)
            {
                Utils.OpenWindow(this, new MainWindow());
            }
        }
    }
}
