using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        private Stopwatch stopwatch;
        private int numCorrectanswers;
        private int numQuestionsLeft;
        public Question(int numQuestions, int answerTime)
        {
            InitializeComponent();
            numCorrectanswers = 0;
            numQuestionsLeft = numQuestions;
            this.CorrectAnswers.Text = numCorrectanswers.ToString();
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.stopwatch = new Stopwatch();
            this.stopwatch.Start();


        }
        /*        
         TODO:make a thread that constantly reduces a second from the seconds left text block and restarts the clock every time a new question is added.
      
         */
        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            int seconds = Convert.ToInt32(this.stopwatch.ElapsedMilliseconds / 1000);

            JObject jObject = new JObject
            {
                [Keys.answerIndex] = 0,
                [Keys.answerTime] = seconds
            };

            Stream.Send(jObject, Codes.SUBMIT_ANSWER);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.SUBMIT_ANSWER))
            {
                if (Convert.ToInt32(response) == 0)
                {
                    this.Answer1.Background = Brushes.Green;
                    numCorrectanswers++;
                    this.CorrectAnswers.Text = numCorrectanswers.ToString();
                }
                else
                {
                    this.Answer1.Background = Brushes.Red;
                    ShowCorrectAnswer(Convert.ToInt32(response));
                }
                this.numQuestionsLeft--;
                if(this.numQuestionsLeft == 0)
                {
                    Utils.OpenWindow(this, new Results());
                }
                this.AnswersLeft.Text = numQuestionsLeft.ToString();
            }
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            this.stopwatch.Stop();
            int seconds = Convert.ToInt32(this.stopwatch.ElapsedMilliseconds / 1000);

            JObject jObject = new JObject
            {
                [Keys.answerIndex] = 1,
                [Keys.answerTime] = seconds
            };
            Stream.Send(jObject, Codes.SUBMIT_ANSWER);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.SUBMIT_ANSWER))
            {
                if (Convert.ToInt32(response) == 1)
                {
                    this.Answer2.Background = Brushes.Green;
                    numCorrectanswers++;
                    this.CorrectAnswers.Text = numCorrectanswers.ToString();
                }
                else
                {
                    this.Answer2.Background = Brushes.Red;
                    ShowCorrectAnswer(Convert.ToInt32(response));
                }
            }
            this.numQuestionsLeft--;
            if (this.numQuestionsLeft == 0)
            {
                Utils.OpenWindow(this, new Results());
            }
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            this.stopwatch.Stop();
            int seconds = Convert.ToInt32(this.stopwatch.ElapsedMilliseconds / 1000);

            JObject jObject = new JObject
            {
                [Keys.answerIndex] = 2,
                [Keys.answerTime] = seconds
            };
            Stream.Send(jObject, Codes.SUBMIT_ANSWER);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.SUBMIT_ANSWER))
            {
                if(Convert.ToInt32(response) == 2)
                {
                    this.Answer3.Background = Brushes.Green;
                    numCorrectanswers++;
                    this.CorrectAnswers.Text = numCorrectanswers.ToString();
                }
                else
                {
                    this.Answer3.Background = Brushes.Red;
                    ShowCorrectAnswer(Convert.ToInt32(response));
                }
            }
            this.numQuestionsLeft--;
            if (this.numQuestionsLeft == 0)
            {
                Utils.OpenWindow(this, new Results());
            }
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            this.stopwatch.Stop();
            int seconds = Convert.ToInt32(this.stopwatch.ElapsedMilliseconds / 1000);

            JObject jObject = new JObject
            {
                [Keys.answerIndex] = 3,
                [Keys.answerTime] = seconds
            };
            Stream.Send(jObject, Codes.SUBMIT_ANSWER);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.SUBMIT_ANSWER))
            {
                if (Convert.ToInt32(response) == 3)
                {
                    this.Answer4.Background = Brushes.Green;
                    numCorrectanswers++;
                    this.CorrectAnswers.Text = numCorrectanswers.ToString();
                }
                else
                {
                    this.Answer4.Background = Brushes.Red;
                    ShowCorrectAnswer(Convert.ToInt32(response));
                }
            }
            this.numQuestionsLeft--;
            if (this.numQuestionsLeft == 0)
            {
                Utils.OpenWindow(this, new Results());
            }
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
        }

        private void ShowCorrectAnswer(int answerIndex)
        {
            switch (answerIndex)
            {
                case 0:
                    this.Answer1.Background = Brushes.Green;
                    break;
                case 1:
                    this.Answer2.Background = Brushes.Green;
                    break;
                case 2:
                    this.Answer3.Background = Brushes.Green;
                    break;
                case 3:
                    this.Answer4.Background = Brushes.Green;
                    break;
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            //dont forget to stop the thread here.
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
