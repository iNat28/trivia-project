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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private int roomId;
        private BackgroundWorker backgroundWorker;
        private Mutex sendingMutex;
        private bool close = false;
        public JoinRoom()
        {
            InitializeComponent();
            sendingMutex = new Mutex();
            User.errorOutput = this.ErrorBox;

            Stream.Send(new JObject(), Codes.GET_ROOM);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.GET_ROOM))
            {
                JArray jArray = (JArray)response.jObject[Keys.rooms];
                foreach (JObject jObject in jArray)
                {
                    this.RoomsList.Items.Add(jObject[Keys.name]);
                }
            }

            backgroundWorker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            backgroundWorker.DoWork += getRoomsList;
            backgroundWorker.ProgressChanged += AddRoomToList;
            backgroundWorker.ProgressChanged += clearRoomsList;
            backgroundWorker.RunWorkerCompleted += GetRoomsCompleted;
            backgroundWorker.RunWorkerAsync();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.RoomsList.SelectedItem != null)
            {
                JObject jObject = new JObject
                {
                    ["roomId"] = this.roomId               
                };
                Stream.Send(jObject, Codes.JOIN_ROOM);

                Response response = Stream.Recieve();
                
                if (Stream.Response(response, Codes.JOIN_ROOM))
                {
                    Utils.OpenWindow(this, new Room(false, this.RoomsList.SelectedItem.ToString(), 0, 0));
                }          
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            backgroundWorker.CancelAsync();
            Utils.OpenWindow(this, new MainWindow());
        }

        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Stream.Send(new JObject(), Codes.GET_ROOM);

            Response response = Stream.Recieve();
            
            if (Stream.Response(response, Codes.GET_ROOM))
            {
                JArray jArray = (JArray)response.jObject[Keys.rooms];
                foreach (JObject jObject in jArray)
                {
                    if (jObject[Keys.name].ToString() == RoomsList.SelectedItem.ToString())
                        this.roomId = Convert.ToInt32(jObject[Keys.id].ToString());
                }
            }

        }

        private void getRoomsList(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (backgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                sendingMutex.WaitOne();

                Stream.Send(new JObject(), Codes.GET_ROOM);

                Response response = Stream.Recieve();

                //If the room is closed
                //TODO: Change code to be room is closed
                if (response.code == Codes.ERROR_CODE)
                {
                    e.Cancel = true;
                    close = true;
                    break;
                }

                //here the rooms list needs to be cleared
                backgroundWorker.ReportProgress(0, (string)"");

                if (Stream.Response(response, Codes.GET_ROOM))
                {
                    JArray jArray = (JArray)response.jObject[Keys.rooms];
                    foreach (JObject jObject in jArray)
                    {
                        backgroundWorker.ReportProgress(0, (string)jObject[Keys.name]);
                    }
                }                                                    
                
                sendingMutex.ReleaseMutex();
                Thread.Sleep(3000);
            }
        }
        private void clearRoomsList(object sender, ProgressChangedEventArgs e)
        {
            if (e.UserState.ToString() == "")
                this.RoomsList.Items.Clear();
        }

        private void AddRoomToList(object sender, ProgressChangedEventArgs e)
        {
            //TODO: need to change user state to rooms        
            if (!this.RoomsList.Items.Contains(e.UserState) && e.UserState.ToString() != "")
            {
                this.RoomsList.Items.Add(e.UserState);
            }
        }

        private void GetRoomsCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (close)
            {
                Utils.OpenWindow(this, new MainWindow());
            }
        }
    }
}
