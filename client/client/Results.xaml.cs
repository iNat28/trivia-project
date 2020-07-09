using Newtonsoft.Json;
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
    /// Interaction logic for Results.xaml
    /// </summary>
    struct MyResults
    {
        public string PlayerName { get; set; }
        public int NumCorrectAnswers { get; set; }
        public int AverageAnswerTime { get; set; }
        public int NumPoints { get; set; }

        public MyResults(string playerName, int numCorrectAnswers, int averageAnswerTime, int numPoints)
        {
            this.PlayerName = playerName;
            this.NumCorrectAnswers = numCorrectAnswers;
            this.AverageAnswerTime = averageAnswerTime;
            this.NumPoints = numPoints;
        }
    }

    public partial class Results : Window
    {
        public Results()
        {            
            InitializeComponent();
            User.errorOutput = this.ErrorOutput;
            User.currentWindow = this;

            Stream.Send(new JObject(), Codes.GET_GAME_RESULTS);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.GET_GAME_RESULTS))
            {
                JArray results = (JArray)response.jObject[Keys.playersResults];

                foreach (var result in results)
                {
                    MyResults playerResult = new MyResults((string)result[Keys.username], (int)result[Keys.numCorrectAnswers], (int)result[Keys.averageAnswerTime], (int)result[Keys.numPoints]);
                    playerStats.Items.Add(playerResult);
                }
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            Utils.OpenWindow(this, new MainWindow());
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
