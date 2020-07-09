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
            
            else
            {
                this.numQuestions = (int)this.NumQuestionsSlider.Value;
                this.numMaxPlayers = (int)this.MaxPlayersSlider.Value;
                this.answerTime = (int)this.AnswerTimeSlider.Value;

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

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            int temp;
            if (int.TryParse(this.QuestionsSliderTextBox.Text, out temp) && Convert.ToInt32(this.QuestionsSliderTextBox.Text) <= this.NumQuestionsSlider.Maximum && Convert.ToInt32(this.QuestionsSliderTextBox.Text) > 0)
                this.NumQuestionsSlider.Value = Convert.ToDouble(this.QuestionsSliderTextBox.Text);
        }

        private void NumQuestionsSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (this.QuestionsSliderTextBox != null)
            {
                this.QuestionsSliderTextBox.Text = this.NumQuestionsSlider.Value.ToString();
            }
        }

        private void AnswerTimeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (this.AnswerTimeTextBox != null)
            {
                this.AnswerTimeTextBox.Text = this.AnswerTimeSlider.Value.ToString();
            }
        }

        private void AnswerTimeTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            int temp;
            if (this.AnswerTimeTextBox == null)
            {
                this.errorOutput.Text = "text box problem";
            }
            else if (int.TryParse(this.AnswerTimeTextBox.Text, out temp) && Convert.ToDouble(this.AnswerTimeTextBox.Text) <= this.AnswerTimeSlider.Maximum && Convert.ToDouble(this.AnswerTimeTextBox.Text) > 0)
                this.AnswerTimeSlider.Value = Convert.ToDouble(this.AnswerTimeTextBox.Text);                      
        }

        private void MaxPlayersSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (this.MaxPlayersTextBox != null)
            {
                this.MaxPlayersTextBox.Text = this.MaxPlayersSlider.Value.ToString();
            }
        }

        private void MaxPlayersTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            int temp;
            if (this.MaxPlayersTextBox == null)
            {
                this.errorOutput.Text = "text box problem";
            }
            else if (int.TryParse(this.MaxPlayersTextBox.Text, out temp) && Convert.ToDouble(this.MaxPlayersTextBox.Text) <= this.MaxPlayersSlider.Maximum && Convert.ToDouble(this.MaxPlayersTextBox.Text) > 0)
                this.MaxPlayersSlider.Value = Convert.ToDouble(this.MaxPlayersTextBox.Text);
        }
    }
}
