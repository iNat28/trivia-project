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
        private int numMaxPlayers;
        private int numQuestions;
        private int answerTime;
        public CreateRoom()
        {
            InitializeComponent();

            User.errorOutput = this.errorOutput;
        }
        
        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {                          
            if (!(this.RoomName.Text == "") && !(this.MaxPlayers.Text == "") && !(this.AnswerTime.Text == "") && !(this.NumQuestion.Text == "") && Convert.ToInt32(this.NumQuestion.Text) > 0 && Convert.ToInt32(this.NumQuestion.Text) < 10)
            {
                this.numQuestions = Convert.ToInt32(this.NumQuestion.Text);
                this.numMaxPlayers = Convert.ToInt32(this.MaxPlayers.Text);
                this.answerTime = Convert.ToInt32(this.AnswerTime.Text);

                JObject jObject = new JObject
                {
                    [Keys.roomName] = this.RoomName.Text,                    
                    [Keys.maxPlayers] = this.numMaxPlayers,                    
                    [Keys.questionsCount] = this.numQuestions,
                    [Keys.timePerQuestion] = this.answerTime,
                    [Keys.username] = User.username
                };
                
                Stream.Send(jObject, Codes.CREATE_ROOM);

                Response response = Stream.Recieve();

                if (Stream.Response(response, Codes.CREATE_ROOM))
                {
                    Utils.OpenWindow(this, new Room(true, new RoomData(0, this.RoomName.Text, this.numMaxPlayers, this.numQuestions, this.answerTime, Room.Status.OPEN)));
                }
            }
            else if(this.NumQuestion.Text != "" && (Convert.ToInt32(this.NumQuestion.Text) <= 0 || Convert.ToInt32(this.NumQuestion.Text) > 10))
            {
                this.errorOutput.Text = "Invalid number of questions";
            }
            else
            {
                this.errorOutput.Text = "One or more fields are empty";
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
