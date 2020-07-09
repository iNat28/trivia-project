using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace client
{
    public abstract class CustomWindow : Window
    {
        public TextBlock ErrorBox;

        public abstract void OnShow(params object[] param);

        protected virtual void OnHide(object sender, CancelEventArgs e)
        {
            if (e != null)
            {
                e.Cancel = true;
            }
        }
    }
}
