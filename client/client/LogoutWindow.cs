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
    public class LogoutWindow : Window
    {
        public static bool toClose = false;

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            if (toClose)
            {
                JObject jObject = new JObject
                {
                    ["username"] = User.username
                };
                Stream.Send(jObject, Codes.LOGOUT);
                Stream.Close();
            }
        }
    }
}
