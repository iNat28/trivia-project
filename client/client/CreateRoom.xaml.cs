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
        }

        protected override Border GetBorder()
        {
            return this.Border;
        }

        public override void OnShow(params object[] param)
        {
            this.RoomName.Text = "";
            this.NumQuestionsSlider.Value = 1;
            this.MaxPlayersSlider.Value = 1;
            this.AnswerTimeSlider.Value = 1;
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.RoomName.Text == "")
            {
                this.ErrorOutput.Text = "Room name field is empty!";
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
                    [Keys.timePerQuestion] = this.answerTime
                };

                Response response = Stream.Send(jObject, Codes.CREATE_ROOM);

                if (Stream.Response(response, Codes.CREATE_ROOM))
                {
                    WindowManager.OpenWindow(WindowTypes.ROOM, true, new RoomData(0, this.RoomName.Text, this.numMaxPlayers, this.numQuestions, this.answerTime, RoomStatus.OPEN));
                }
            }           
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.MAIN);
        }

        private void QuestionsSliderTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            this.UpdateSlider(this.NumQuestionsSlider, this.QuestionsSliderTextBox);
        }

        private void NumQuestionsSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            this.UpdateTextBox(this.QuestionsSliderTextBox, this.NumQuestionsSlider);
        }

        private void AnswerTimeSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            this.UpdateTextBox(this.AnswerTimeTextBox, this.AnswerTimeSlider);
        }

        private void AnswerTimeTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            this.UpdateSlider(this.AnswerTimeSlider, this.AnswerTimeTextBox);
        }

        private void MaxPlayersSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            this.UpdateTextBox(this.MaxPlayersTextBox, this.MaxPlayersSlider);
        }

        private void MaxPlayersTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            this.UpdateSlider(this.MaxPlayersSlider, this.MaxPlayersTextBox);
        }

        private void UpdateSlider(Slider slider, TextBox textBox)
        {
            double value;

            if(slider == null || textBox == null)
            {
                return;
            }

            if (int.TryParse(textBox.Text, out _))
            {
                value = Convert.ToDouble(textBox.Text);

                if (value > slider.Maximum)
                {
                    textBox.Text = slider.Maximum.ToString();
                }
                else if (value < slider.Minimum)
                {
                    textBox.Text = slider.Minimum.ToString();
                }

                slider.Value = value;
            }
            else
            {
                textBox.Text = slider.Minimum.ToString();
            }
        }

        private void UpdateTextBox(TextBox textBox, Slider slider)
        {
            if (slider == null || textBox == null)
            {
                return;
            }

            textBox.Text = slider.Value.ToString();
        }

        public override TextBlock GetErrorOutput()
        {
            return this.ErrorOutput;
        }
    }
}
