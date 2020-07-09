using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
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
        public string AverageAnswerTime { get; set; }
        public int NumPoints { get; set; }

        public MyResults(string playerName, int numCorrectAnswers, double averageAnswerTime, int numPoints)
        {
            this.PlayerName = playerName;
            this.NumCorrectAnswers = numCorrectAnswers;
            this.AverageAnswerTime = averageAnswerTime.ToString("0.00");
            this.NumPoints = numPoints;
        }
    }

    public partial class ResultsWindow : CustomWindow
    {
        public ResultsWindow()
        {            
            InitializeComponent();
        }

        public override void OnShow(params object[] param)
        {
            base.ErrorOutput = this.ErrorBox;
            playerStats.Items.Clear();

            Response response = Stream.Send(Codes.GET_GAME_RESULTS);

            if (Stream.Response(response, Codes.GET_GAME_RESULTS))
            {
                JArray results = (JArray)response.jObject[Keys.playersResults];

                foreach (var result in results)
                {
                    MyResults playerResult = new MyResults((string)result[Keys.username], (int)result[Keys.numCorrectAnswers], (double)result[Keys.averageAnswerTime], (int)result[Keys.numPoints]);
                    playerStats.Items.Add(playerResult);
                }
            }
        }

        protected override void OnHide(object sender, CancelEventArgs e)
        {
            if (!WindowManager.exit)
            {
                base.OnHide(sender, e);
                WindowManager.OpenWindow(WindowTypes.MAIN);
            }
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.MAIN);
        }
    }
}
