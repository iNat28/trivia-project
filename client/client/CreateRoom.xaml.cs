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
    //TODO: when the user chooses stats for the game, make them tickers
    public partial class CreateRoomWindow : LogoutWindow
    {       
        private int numMaxPlayers;
        private int numQuestions;
        private int answerTime;
        
        public CreateRoomWindow()
        {
            InitializeComponent();

            base.ErrorOutput = this.errorOutput;
        }
        
        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if(this.RoomName.Text == "")
            {
                this.errorOutput.Text = "Room name field is empty!";
            }
            else if (this.MaxPlayers.Text == "")
            {
                this.errorOutput.Text = "Max players field is empty!";
            }
            else if (this.AnswerTime.Text == "")
            {
                this.errorOutput.Text = "Answer time field is empty!";
            }
            else if (this.NumQuestion.Text == "")
            {
                this.errorOutput.Text = "Num questions field is empty!";
            }
            else
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
                    WindowManager.OpenWindow(WindowTypes.ROOM, new RoomData(0, this.RoomName.Text, this.numMaxPlayers, this.numQuestions, this.answerTime, RoomWindow.Status.OPEN));
                }
            }           
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.MAIN);
        }
    }
}
