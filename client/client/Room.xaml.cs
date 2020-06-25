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
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : LogoutWindow
    {
        public Room(bool isAdmin, string roomName, int maxPlayers, int answerTime)
        {
            InitializeComponent();

            User.errorOutput = this.errorOutput;

            if (isAdmin)
                this.LeaveRoomButton.Visibility = Visibility.Hidden;
            else
            {
                this.CloseRoomButton.Visibility = Visibility.Hidden;
                this.StartGameButton.Visibility = Visibility.Hidden;
            }
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //get list of usernames in the room and add then to the list like this:
            //listBox1.Items.Add(textBox1.Text);
            //this.NamesList.Items.Add("bla bla");
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {
            //starts game
        }

        private void CloseRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }

        private void LeaveGameButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
