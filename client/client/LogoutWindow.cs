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
using System.ComponentModel;
using Newtonsoft.Json.Linq;

namespace client
{
    public abstract class LogoutWindow : CustomWindow
    {
        protected override void OnHide(object sender, CancelEventArgs e)
        {
            if (!WindowManager.exit)
            {
                if (e != null)
                {
                    e.Cancel = true;
                }
                Stream.Signout();
                WindowManager.Close();
            }
        }
    }
}
