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
    public struct RoomData
    {
        public int id;
        public string name;
        public int maxPlayers;
        public int questionsCount;
        public int timePerQuestion;
        public RoomWindow.Status roomStatus;

        public RoomData(int id, string name, int maxPlayers, int questionsCount, int timePerQuestion, RoomWindow.Status roomStatus)
        {
            this.id = id;
            this.name = name;
            this.maxPlayers = maxPlayers;
            this.questionsCount = questionsCount;
            this.timePerQuestion = timePerQuestion;
            this.roomStatus = roomStatus;
        }

        public override bool Equals(object obj)
        {
            return obj is RoomData data &&
                   id == data.id &&
                   name == data.name &&
                   maxPlayers == data.maxPlayers &&
                   questionsCount == data.questionsCount &&
                   timePerQuestion == data.timePerQuestion &&
                   roomStatus == data.roomStatus;
        }

        public override int GetHashCode()
        {
            var hashCode = -1434586793;
            hashCode = hashCode * -1521134295 + id.GetHashCode();
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(name);
            hashCode = hashCode * -1521134295 + maxPlayers.GetHashCode();
            hashCode = hashCode * -1521134295 + questionsCount.GetHashCode();
            hashCode = hashCode * -1521134295 + timePerQuestion.GetHashCode();
            hashCode = hashCode * -1521134295 + roomStatus.GetHashCode();
            return hashCode;
        }

        public override string ToString()
        {
            return this.name + " | Max players: " + this.maxPlayers + " | Number of questions: " + this.questionsCount + " | Time per questions: " + this.timePerQuestion + 
                " | Room status: " + this.roomStatus;
        }
    };


    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoomWindow : LogoutWindow
    {
        private RoomData selectedRoom;
        private readonly BackgroundWorker backgroundWorker;
        private Mutex sendingMutex;
        private readonly List<RoomData> rooms;
        
        //TODO: Need to show the rooms and all of it's room state, and if it's game started, or if it is maxed out for players
        
        public JoinRoomWindow()
        {
            InitializeComponent();
            this.rooms = new List<RoomData>();

            backgroundWorker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            backgroundWorker.DoWork += GetRoomsList;
            backgroundWorker.ProgressChanged += ChangeWPF;
        }

        public override void OnShow(params object[] param)
        {
            base.ErrorOutput = this.ErrorBox;
            this.rooms.Clear();
            this.RoomsList.Items.Clear();
            this.sendingMutex?.Close();
            this.sendingMutex = new Mutex();
            backgroundWorker.RunWorkerAsync();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            sendingMutex.WaitOne();

            if(this.RoomsList.SelectedItem == null)
            {
                this.ErrorOutput.Text = "Room not selected!";
                return;
            }

            JObject jObject = new JObject
            {
                [Keys.roomId] = selectedRoom.id
            };
            Response response = Stream.Send(jObject, Codes.JOIN_ROOM);

            if (Stream.Response(response, Codes.JOIN_ROOM) && this.RoomsList.SelectedItem != null)
            {
                backgroundWorker.CancelAsync();
                
                WindowManager.OpenWindow(WindowTypes.ROOM, false, this.selectedRoom);
            }
            sendingMutex.ReleaseMutex();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            backgroundWorker.CancelAsync();
            WindowManager.OpenWindow(WindowTypes.MAIN);
        }

        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (this.RoomsList.SelectedIndex > -1)
            {
                this.selectedRoom = this.rooms[this.RoomsList.SelectedIndex];
            }
        }

        private void GetRoomsList(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (backgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                sendingMutex.WaitOne();

                Response response = Stream.Send(Codes.GET_ROOM);

                if (Stream.ResponseForThread(response, Codes.GET_ROOM, out string error))
                {
                    JArray jArray = (JArray)response.jObject[Keys.rooms];
                    
                    List<RoomData> newRooms = new List<RoomData>();

                    foreach (JObject jObject in jArray)
                    {
                        RoomData room = new RoomData(
                            (int)jObject[Keys.id],
                            (string)jObject[Keys.roomName],
                            (int)jObject[Keys.maxPlayers],
                            (int)jObject[Keys.questionsCount],
                            (int)jObject[Keys.timePerQuestion],
                            (RoomWindow.Status)(int)jObject[Keys.roomStatus]
                        );
                        if (!this.rooms.Contains(room))
                        {
                            this.rooms.Add(room);
                            backgroundWorker.ReportProgress(1, room.ToString());
                        }
                        newRooms.Add(room);
                    }

                    for(int i = this.rooms.Count - 1; i >= 0; i--)
                    {
                        if (!newRooms.Contains(this.rooms[i]))
                        {
                            backgroundWorker.ReportProgress(2, this.rooms[i].ToString());
                            this.rooms.RemoveAt(i);
                        }
                    }
                }
                else
                {
                    if (error == "exit")
                    {
                        e.Cancel = true;
                        break;
                    }
                    backgroundWorker.ReportProgress(3, error);
                }

                sendingMutex.ReleaseMutex();
                Thread.Sleep(500);
            }
        }

        private void ChangeWPF(object sender, ProgressChangedEventArgs e)
        {
            string param = (string)e.UserState;
            switch (e.ProgressPercentage)
            {
                case 1:
                    this.RoomsList.Items.Add(param);
                    break;
                case 2:
                    this.RoomsList.Items.Remove(param);
                    break;
                case 3:
                    this.ErrorOutput.Text = param;
                    break;
            }
        }
    }
}
