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
    struct myResults
    {        
        private string playerName;
        private int numCorrectAnswers;
        private int averageAnswerTime;
        private int numPoints;

        public myResults(string playerName, int numCorrectAnswers, int averageAnswerTime, int numPoints)
        {
            this.playerName = playerName;
            this.numCorrectAnswers = numCorrectAnswers;
            this.averageAnswerTime = averageAnswerTime;
            this.numPoints = numPoints;
        }
    }
    public partial class Results : Window
    {
        private DataGrid playerStats = new DataGrid();
        public Results()
        {            
            InitializeComponent();
            createTable();           

            Stream.Send(new JObject(), Codes.GET_GAME_RESULTS);

            Response response = Stream.Recieve();
           
            if (Stream.Response(response, Codes.GET_GAME_RESULTS))
            {
                JArray results = (JArray)response.jObject[Keys.playersResults];
                
                foreach (var result in results)
                {
                    myResults playerResult = new myResults((string)result[Keys.username], (int)result[Keys.numCorrectAnswers], (int)result[Keys.averageAnswerTime], (int)result[Keys.numPoints]);
                    playerStats.Items.Add(playerResult);
                }
            }
        }
        private void createTable()
        {
            this.playerStats.HorizontalAlignment = HorizontalAlignment.Left;
            this.playerStats.Height = 278;
            this.playerStats.VerticalAlignment = VerticalAlignment.Top;
            this.playerStats.Margin = new Thickness(177,37,0,0);
            this.playerStats.Width = 448;
            
            DataGridTextColumn col1 = new DataGridTextColumn();
            DataGridTextColumn col2 = new DataGridTextColumn();
            DataGridTextColumn col3 = new DataGridTextColumn();
            DataGridTextColumn col4 = new DataGridTextColumn();

            this.playerStats.Columns.Add(col1);
            this.playerStats.Columns.Add(col2);
            this.playerStats.Columns.Add(col3);
            this.playerStats.Columns.Add(col4);

            col1.Binding = new Binding("PLAYER NAME");
            col2.Binding = new Binding("NUM OF CORRECT ANSWERS");
            col3.Binding = new Binding("AVERAGE ANSWER TIME");
            col4.Binding = new Binding("TOTAL POINTS");

            col1.Header = "PLAYER NAME";
            col2.Header = "NUM OF CORRECT ANSWERS";
            col3.Header = "AVERAGE ANSWER TIME";
            col4.Header = "TOTAL POINTS";          
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
