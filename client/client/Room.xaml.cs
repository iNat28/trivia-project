using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
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
        private int roomId;
        private static Boolean updateUserList;
        public Room(bool isAdmin, string roomName, int maxPlayers, int answerTime)
        {
            InitializeComponent();

            User.errorOutput = this.errorOutput;

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

            if (Stream.Response(response, Codes.GET_ROOM, this.errorOutput))
            {
                JArray jArray = (JArray)response.jObject[Keys.rooms];
                foreach (JObject jObject in jArray)
                {
                    if (jObject[Keys.name].ToString() == roomName)
                        this.roomId = Convert.ToInt32(jObject[Keys.id].ToString());
                }
            }
            updateUserList = true;
            //adding users
            ThreadStart usersThreadStart = new ThreadStart(showUsersList);
            Thread usersThread = new Thread(usersThreadStart);
            usersThread.Start();
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
            Utils.OpenWindow(this, new MainWindow());
        }

        private void LeaveGameButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }

        private void showUsersList()
        {
            //TODO: add thread that does the following every 3 mins
            while (updateUserList)
            {
                Stream.Send(new JObject(), Codes.GET_PLAYERS_IN_ROOM);

                Response usersResponse = Stream.Recieve();

                if (Stream.Response(usersResponse, Codes.GET_PLAYERS_IN_ROOM, this.errorOutput))
                {
                    JArray jArray = (JArray)usersResponse.jObject[Keys.playersInRoom];
                    foreach (JObject jObject in jArray)
                    {
                        this.NamesList.Items.Add(jObject[Keys.username]);
                    }
                }
                Thread.Sleep(3000);
            }
        }
    }
}
