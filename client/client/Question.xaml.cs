using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
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
        private int timeLeft;
        //mutex
        private Mutex mtx;

        //threads
        private BackgroundWorker updatingThread;
        private BackgroundWorker timeThread;

        public Question(int numQuestions, int answerTime)
        {
            InitializeComponent();
            numCorrectanswers = 0;
            numQuestionsLeft = numQuestions;
            //updating the beggining stats
            this.CorrectAnswers.Text = numCorrectanswers.ToString();
            this.timeLeft = answerTime;
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.TimeLeft.Text = answerTime.ToString();
            //creating the stopwatch
            this.stopwatch = new Stopwatch();
                        

            //starting threads
            this.mtx = new Mutex();            

            this.updatingThread = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            this.timeThread = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            this.stopwatch.Start();

            this.updatingThread.DoWork += getNewQuestion;
            this.updatingThread.ProgressChanged += updateNewQuestion;
            this.updatingThread.RunWorkerCompleted += gameCompleted;
            this.updatingThread.RunWorkerAsync();

            this.timeThread.DoWork += updateTime;                       
            this.timeThread.RunWorkerAsync();
           
            
        }

        private void updateTime(object sender, DoWorkEventArgs e)
        {
            int timeTemp;
            while(true)
            {
                if (this.updatingThread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }
                this.mtx.WaitOne();
                timeTemp = Convert.ToInt32(this.TimeLeft.Text);
                this.TimeLeft.Text = (timeTemp--).ToString();
                this.mtx.ReleaseMutex();
                Thread.Sleep(1000);
            }
        }

        private void getNewQuestion(object sender, DoWorkEventArgs e)
        {            
            int questionsTemp = this.numQuestionsLeft;
            while(questionsTemp != 0)
            {
                if (this.updatingThread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                this.mtx.WaitOne();
                if (Convert.ToInt32(this.TimeLeft.Text) == 0 || questionsTemp == this.numQuestionsLeft + 1)
                {
                    //get new question info
                    Stream.Send(new JObject(), Codes.GET_QUESTION);

                    Response usersResponse = Stream.Recieve();
                    
                    string error;
                    if (Stream.ResponseForThread(usersResponse, Codes.GET_QUESTION, out error))
                    {
                        this.updatingThread.ReportProgress(0, usersResponse);
                    }

                    questionsTemp--;
                    //restarting the time
                    this.stopwatch.Restart();
                    this.TimeLeft.Text = this.timeLeft.ToString();                    
                }
                this.mtx.ReleaseMutex();
                Thread.Sleep(1000);
            }
        }

        private void updateNewQuestion(object sender, ProgressChangedEventArgs e)
        {
            //changes the xaml file
            //TODO: add text blocks for difficulty and category
            JObject param = (JObject)e.UserState;

            this.QuestionText.Text = param[Keys.question].ToString();
            this.Difficulty.Text = param[Keys.difficulty].ToString();
            this.Category.Text = param[Keys.category].ToString();

            JArray jArray = (JArray)param[Keys.answers];

            this.Answer1.Content = jArray[0].ToString();
            this.Answer2.Content = jArray[1].ToString();
            //if there are only two answers

            if(jArray.Count == 2)
            {
                this.Answer3.Visibility = Visibility.Hidden;
                this.Answer4.Visibility = Visibility.Hidden;
            }
            else
            {
                this.Answer3.Visibility = Visibility.Visible;
                this.Answer4.Visibility = Visibility.Visible;

                this.Answer3.Content = jArray[2].ToString();
                this.Answer4.Content = jArray[3].ToString();
            }
        }

        private void gameCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            //opens new window
            Utils.OpenWindow(this, new Results());
        }
        
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
