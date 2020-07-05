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

namespace client
{
    /// <summary>
    /// Interaction logic for Question.xaml
    /// </summary>
    public partial class Question : Window
    {
        public Question()
        {
            InitializeComponent();

        }
        /*TODO: for each button: check if the answer is the correct one.
         if it is, then add one to the correct answers.
         regardless, reduce one from the questions left.
         the whole thing should be a loop to constantly get the next question and place the question and answers in their text blocks.

         TODO: there should also be a thread that constantly reduces a second from the seconds left text block and restarts the clock every time a new question is added.

         TODO: there should also be an algorithm to randomly chhose which button gets which answer.

         TODO: there should be a way to determine if the admin is the one who left the game. if so then the room should exit for everyone.
         */
        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {

        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            //dont forget to stop the thread here.
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
