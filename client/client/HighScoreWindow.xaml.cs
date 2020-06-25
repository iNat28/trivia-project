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
            User.errorOutput = this.errorOutput;

            InitializeComponent();

            Stream.Send(new JObject(), Codes.HIGH_SCORES);

            Response response = Stream.Recieve();
            if (Stream.Response(response, Codes.HIGH_SCORES, errorOutput))
            {
                errorOutput.Text = response.jObject.ToString();
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new Statistics());
        }
    }
}
