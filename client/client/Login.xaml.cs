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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using System.IO;
using Newtonsoft.Json.Linq;

namespace client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class LoginWindow : CustomWindow
    {
        public LoginWindow()
        {
            InitializeComponent();
            base.ErrorOutput = this.errorOutput;
        }

        protected override void OnClosed(EventArgs e)
        {
            WindowManager.Close();
        }

        //Move to functions and classes
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            JObject login = new JObject
            {
                ["username"] = usernameInput.Text,
                ["password"] = passwordInput.Password
            };

            Stream.Send(login, Codes.LOGIN);

            Response response = Stream.Recieve();

            if(Stream.Response(response, Codes.LOGIN))
            {
                User.username = (string)login["username"];
                WindowManager.OpenWindow(WindowTypes.MAIN);
            }
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.SIGN_UP);
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.Close();
        }
    }
}
