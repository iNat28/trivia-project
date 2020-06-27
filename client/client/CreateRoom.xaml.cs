using Newtonsoft.Json.Linq;
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
    public partial class CreateRoom : LogoutWindow
    {
        public CreateRoom()
        {
            InitializeComponent();

            User.errorOutput = this.errorOutput;
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
                    [Keys.id] = 0,
                    [Keys.roomName] = this.RoomName.Text,
                    [Keys.maxUsers] = Convert.ToInt32(this.MaxPlayers.Text),
                    [Keys.timePerQuestion] = Convert.ToInt32(this.AnswerTime.Text),
                    [Keys.isActive] = 0,
                    [Keys.numQuestionsAsked] = 0
                };
                
                Stream.Send(jObject, Codes.CREATE_ROOM);

                Response response = Stream.Recieve();

                if (Stream.Response(response, Codes.CREATE_ROOM))
                    Utils.OpenWindow(this, new Room(true, this.RoomName.Text, Convert.ToInt32(this.MaxPlayers.Text), Convert.ToInt32(this.AnswerTime.Text)));
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
