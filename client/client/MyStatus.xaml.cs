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
using Newtonsoft.Json.Linq;

namespace client
{
    /// <summary>
    /// Interaction logic for MyStatus.xaml
    /// </summary>
    public partial class MyStatus : LogoutWindow
    {
        public MyStatus()
        {
            InitializeComponent();
            User.errorOutput = errorOutput;
            User.currentWindow = this;

            Stream.Send(new JObject(), Codes.USER_STATS);

            Response response = Stream.Recieve();
            if (Stream.Response(response, Codes.USER_STATS))
            {
                JObject userStats = (JObject)response.jObject[Keys.userStats];
                this.numPointsOutput.Text = "Number of Points - " + (int)userStats[Keys.numPoints];
                this.numOfGamesOutput.Text = "Number of Games - " + (int)userStats[Keys.numTotalGames];
                this.numOfRightAnswersOutput.Text = "Number of Right Answers - " + (int)userStats[Keys.numCorrectAnswers];
                this.numOfWrongAnswersOutput.Text = "Number of Wrong Answers - " + (int)userStats[Keys.numWrongAnswers];
                this.avgTimeForAnswersOutput.Text = "Average answer time - " + (int)userStats[Keys.averageAnswerTime];

                response.jObject.ToString();
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new Statistics());
        }
    }
}
