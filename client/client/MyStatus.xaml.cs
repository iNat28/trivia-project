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
    public partial class MyStatusWindow : LogoutWindow
    {
        public MyStatusWindow()
        {
            InitializeComponent();
        }

        public override void OnShow(params object[] param)
        {
            Response response = Stream.Send(Codes.USER_STATS);
            if (Stream.Response(response, Codes.USER_STATS))
            {
                this.numPointsOutput.Text = "Number of Points: " + (int)response.jObject[Keys.numPoints];
                this.numOfGamesOutput.Text = "Number of Games: " + (int)response.jObject[Keys.numTotalGames];
                this.numOfRightAnswersOutput.Text = "Number of Correct Answers: " + (int)response.jObject[Keys.numCorrectAnswers];
                this.numOfWrongAnswersOutput.Text = "Number of Wrong Answers: " + (int)response.jObject[Keys.numWrongAnswers];
                this.avgTimeForAnswersOutput.Text = "Average answer time: " + ((double)response.jObject[Keys.averageAnswerTime]).ToString("0.00");

                response.jObject.ToString();
            }
        }

        public override TextBlock GetErrorOutput()
        {
            return this.ErrorOutput;
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.STATISTICS);
        }
    }
}
