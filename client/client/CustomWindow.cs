using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace client
{
    public class CustomWindow : Window
    {
        protected TextBlock ErrorOutput;

        public virtual void OnShow(params object[] param)
        {
        }

        public virtual void OnHide(params object[] param)
        {
        }
    }
}
