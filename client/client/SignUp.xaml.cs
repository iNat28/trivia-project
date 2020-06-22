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
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUpWindow : Window
    {
        //TODO: Add verify password
        public SignUpWindow()
        {
            InitializeComponent();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new LoginWindow());
        }

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                JObject signUp = new JObject
                {
                    ["username"] = usernameInput.Text,
                    ["password"] = passwordInput.Password,
                    ["email"] = emailInput.Text
                };

                Stream.Send(signUp, Codes.SIGNUP);

                Response response = Stream.Recieve();

                if (Stream.Response(response, Codes.SIGNUP, errorOutput))
                {
                    Utils.OpenWindow(this, new MainWindow((string)signUp["username"]));
                }
            }
            catch (Exception exception)
            {
                errorOutput.Text = exception.Message;
            }
        }
    }
}
