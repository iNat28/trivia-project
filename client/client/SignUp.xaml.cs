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
using Newtonsoft.Json.Linq;

namespace client
{
    /// <summary>
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUpWindow : CustomWindow
    {
        public SignUpWindow()
        {
            InitializeComponent();
        }

        public override void OnShow(params object[] param)
        {
            base.ErrorOutput = this.ErrorOutput;

            this.usernameInput.Text = "";
            this.passwordInput.Password = "";
            this.emailInput.Text = "";
        }

        protected override void OnHide(object sender, CancelEventArgs e)
        {
            WindowManager.Close();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            WindowManager.OpenWindow(WindowTypes.LOGIN);
        }

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            JObject signUp = new JObject
            {
                ["username"] = usernameInput.Text,
                ["password"] = passwordInput.Password,
                ["email"] = emailInput.Text
            };

            Response response = Stream.Send(signUp, Codes.SIGNUP);

            if (Stream.Response(response, Codes.SIGNUP))
            {
                User.username = (string)signUp["username"];
                WindowManager.OpenWindow(WindowTypes.MAIN);
            }
        }
    }
}
