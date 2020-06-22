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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        public Statistics()
        {
            InitializeComponent();
        }

        private void MyStatusButton_Click(object sender, RoutedEventArgs e)
        {
            //moves to my status page
            Utils.OpenWindow(this, new MyStatus());
        }

        private void HighScoresButton_Click(object sender, RoutedEventArgs e)
        {
            //moves to high scores page
            Utils.OpenWindow(this, new HighScoreWindow());
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            //moves back to main window
            
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
