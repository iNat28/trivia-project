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
    /// Interaction logic for Main.xaml
    /// </summary>
    public partial class MainWindow : LogoutWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public override void OnShow(params object[] param)
        {
            base.ErrorOutput = this.errorOutput;

            UsernameHeader.Text = "Hello " + User.username;
        }

        private void SignoutButton_Click(object sender, RoutedEventArgs e)
        {
            Stream.Signout();
            WindowManager.OpenWindow(WindowTypes.LOGIN);
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.CREATE_ROOM);
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.JOIN_ROOM);
        }

        private void StatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.STATISTICS);
        }
    }
}
