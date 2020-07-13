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
    /// Interaction logic for HighScoreWindow.xaml
    /// </summary>
    public partial class HighScoreWindow : LogoutWindow
    {
        public HighScoreWindow()
        {
            InitializeComponent();
        }

        public override void OnShow(params object[] param)
        {
            Response response = Stream.Send(Codes.HIGH_SCORES);
            if (Stream.Response(response, Codes.HIGH_SCORES))
            {
                JArray jArray = (JArray)response.jObject[Keys.highScores];
                foreach (JObject jObject in jArray)
                {
                    this.highScores.Items.Add((string)jObject[Keys.username] + " - " + (int)jObject[Keys.numPoints]);
                }
            }
        }

        public override TextBlock GetErrorOutput()
        {
            return this.ErrorOutput;
        }

        protected override Border GetBorder()
        {
            return this.Border;
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.STATISTICS);
        }
    }
}
