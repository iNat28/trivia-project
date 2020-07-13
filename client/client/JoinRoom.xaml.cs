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
        public int currentPlayerCount;
        public int questionsCount;
        public int timePerQuestion;
        public RoomStatus roomStatus;

        public RoomData(int id, string name, int maxPlayers, int questionsCount, int timePerQuestion, RoomStatus roomStatus, int currentPlayerCount = 1)
        {
            this.id = id;
            this.name = name;
            this.maxPlayers = maxPlayers;
            this.currentPlayerCount = currentPlayerCount;
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
                   currentPlayerCount == data.currentPlayerCount &&
                   questionsCount == data.questionsCount &&
                   timePerQuestion == data.timePerQuestion &&
                   roomStatus == data.roomStatus;
        }

        public override int GetHashCode()
        {
            var hashCode = 1280019825;
            hashCode = hashCode * -1521134295 + id.GetHashCode();
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(name);
            hashCode = hashCode * -1521134295 + maxPlayers.GetHashCode();
            hashCode = hashCode * -1521134295 + currentPlayerCount.GetHashCode();
            hashCode = hashCode * -1521134295 + questionsCount.GetHashCode();
            hashCode = hashCode * -1521134295 + timePerQuestion.GetHashCode();
            hashCode = hashCode * -1521134295 + roomStatus.GetHashCode();
            return hashCode;
        }

        public override string ToString()
        {
            string roomStatus = "";

            if(this.roomStatus == RoomStatus.GAME_STARTED)
            {
                roomStatus = " | Game in session";
            }

            return
                "Room: " + this.name + " | " + 
                this.currentPlayerCount + '/' + this.maxPlayers + " players | " +
                Utils.GetProperString(this.questionsCount, "question") + " | " +
                Utils.GetProperString(this.timePerQuestion, "second") + " per question"
                + roomStatus;
        }
    };

    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoomWindow : LogoutWindow
    {
        private RoomData selectedRoom;
        private readonly BackgroundWorker backgroundWorker;
        private readonly Mutex sendingMutex;
        private readonly List<RoomData> rooms;

        private enum ThreadCodes
        {
            ADD_ROOM,
            REMOVE_ROOM,
            PRINT_ERROR
        }

        public JoinRoomWindow()
        {
            InitializeComponent();
            this.rooms = new List<RoomData>();
            this.sendingMutex = new Mutex();

            backgroundWorker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            backgroundWorker.DoWork += GetRoomsList;
            backgroundWorker.ProgressChanged += ChangeWPF;
            backgroundWorker.RunWorkerCompleted += WorkerFinished;
        }

        protected override Border GetBorder()
        {
            return this.Border;
        }

        public override void OnShow(params object[] param)
        {
            this.rooms.Clear();
            this.RoomsList.Items.Clear();
            this.sendingMutex.WaitOne();

            this.backgroundWorker.RunWorkerAsync();
            this.sendingMutex.ReleaseMutex();
        }

        public override TextBlock GetErrorOutput()
        {
            return this.ErrorOutput;
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

                Response response = Stream.Send(Codes.GET_ROOM, false);

                if (Stream.ResponseForThread(response, Codes.GET_ROOM, out string error))
                {
                    JArray jArray = (JArray)response.jObject[Keys.rooms];
                    
                    List<RoomData> newRooms = new List<RoomData>();

                    foreach (JObject jObject in jArray)
                    {
                        RoomData room = new RoomData(
                            (int)jObject[Keys.roomId],
                            (string)jObject[Keys.roomName],
                            (int)jObject[Keys.maxPlayers],
                            (int)jObject[Keys.questionsCount],
                            (int)jObject[Keys.timePerQuestion],
                            (RoomStatus)(int)jObject[Keys.roomStatus],
                            (int)jObject[Keys.currentPlayerCount]
                        );
                        if (!this.rooms.Contains(room))
                        {
                            this.rooms.Add(room);
                            backgroundWorker.ReportProgress((int)ThreadCodes.ADD_ROOM, room.ToString());
                        }
                        newRooms.Add(room);
                    }

                    for(int i = this.rooms.Count - 1; i >= 0; i--)
                    {
                        if (!newRooms.Contains(this.rooms[i]))
                        {
                            backgroundWorker.ReportProgress((int)ThreadCodes.REMOVE_ROOM, this.rooms[i].ToString());
                            this.rooms.RemoveAt(i);
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
                case ThreadCodes.ADD_ROOM:
                    this.RoomsList.Items.Add(param);
                    break;
                case ThreadCodes.REMOVE_ROOM:
                    this.RoomsList.Items.Remove(param);
                    break;
                case ThreadCodes.PRINT_ERROR:
                    this.ErrorOutput.Text = param;
                    break;
            }
        }

        private void WorkerFinished(object sender, RunWorkerCompletedEventArgs e)
        {
            if (Stream.backendClosed)
            {
                Stream.Close();
                return;
            }
        }
    }
}
