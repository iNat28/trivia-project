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
    /// Interaction logic for MyStatus.xaml
    /// </summary>
    public partial class MyStatus : LogoutWindow
    {
        public MyStatus()
        {
            try
            {
                InitializeComponent();

                Stream.Send(new JObject(), Codes.USER_STATS);

                Response response = Stream.Recieve();
                if (Stream.Response(response, Codes.USER_STATS, errorOutput))
                {
                    errorOutput.Text = response.jObject.ToString();
                }
            }
            catch (Exception exception)
            {
                errorOutput.Text = exception.Message;
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new Statistics());
        }
    }
}
