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
using Newtonsoft.Json.Bson;

namespace client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }

        //Move to functions and classes
        private void loginButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                TcpClient client = new TcpClient();
                client.Connect(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 40200));
                NetworkStream clientStream = client.GetStream();

                JObject login = new JObject();
                login["username"] = usernameInput.Text;
                login["password"] = passwordInput.Password;

                MemoryStream memoryStream = new MemoryStream();
                BsonDataWriter bsonWriter = new BsonDataWriter(memoryStream);
                login.WriteTo(bsonWriter);

                byte[] buffer = new byte[] { Convert.ToByte(10) };
                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Write(memoryStream.ToArray(), 0, (int)memoryStream.Length);
                clientStream.Flush();

                byte[] bufferRead = new byte[5];
                clientStream.Read(bufferRead, 0, bufferRead.Length);
                int code = Convert.ToInt32(bufferRead[0]);
                int size = BitConverter.ToInt32(bufferRead, 1);
                byte[] response = new byte[size + 4];
                Array.Copy(bufferRead, 1, response, 0, 4);
                clientStream.Read(response, 4, response.Length - 4);

                JObject jObject = (JObject)JToken.ReadFrom(new BsonDataReader(new MemoryStream(response)));
                
                switch(code)
                {
                    case 0:
                        errorOutput.Text = (string)jObject["message"];
                        break;
                    case 10:
                        this.Hide();
                        MainWindow main = new MainWindow();
                        main.ShowDialog();
                        this.Close();
                        break;
                    default:
                        errorOutput.Text = jObject.ToString();
                        break;
                }

            }
            catch (SocketException socketException)
            {
                errorOutput.Text = socketException.Message;
            }
        }

        private void signUpButton_Click(object sender, RoutedEventArgs e)
        {
            this.Hide();
            SignUpWindow signUp = new SignUpWindow();
            signUp.ShowDialog();
            this.Show();
        }

        private void exitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
