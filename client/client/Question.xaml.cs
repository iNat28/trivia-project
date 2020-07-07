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
        //private int timeTemp;
        //private bool wait = false;
        //mutex
        private Mutex mtx;
        private Mutex timeMutex;
        private int currentTime;

        //threads
        private BackgroundWorker updatingThread;
        private BackgroundWorker timeThread;

        public Question(int numQuestions, int answerTime)
        {
            InitializeComponent();
            numCorrectanswers = 0;
            currentTime = 0;
            numQuestionsLeft = numQuestions;
            //updating the beggining stats
            this.CorrectAnswers.Text = numCorrectanswers.ToString();
            this.timeLeft = answerTime;
            //this.timeTemp = this.timeLeft;
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.TimeLeft.Text = answerTime.ToString();
            //creating the stopwatch
            this.stopwatch = new Stopwatch();
                        

            //starting threads
            this.mtx = new Mutex();
            this.timeMutex = new Mutex();

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

            this.getQuestion();

            this.updatingThread.DoWork += UpdateQuestions;
            this.updatingThread.ProgressChanged += UpdateThreadProgress;
            this.updatingThread.RunWorkerCompleted += gameCompleted;

            this.timeThread.DoWork += updateTime;
            this.timeThread.ProgressChanged += changeTimeBox;
            this.timeThread.RunWorkerAsync();

            this.stopwatch.Start();
        }

        private void updateTime(object sender, DoWorkEventArgs e)
        {
            //TODO: Try to move the submit answer and get question functionality for this thread, after the time is finished
            while (true)
            {
                if (this.timeThread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }
                this.mtx.WaitOne();

                this.timeThread.ReportProgress(0, "");
                this.mtx.ReleaseMutex();
                Thread.Sleep(1000);
            }
        }

        private void changeTimeBox(object sender, ProgressChangedEventArgs e)
        {
            this.timeMutex.WaitOne();
            int timerTemp;

            timerTemp = Convert.ToInt32(this.TimeLeft.Text);
            timerTemp--;
            this.TimeLeft.Text = timerTemp.ToString();
            //this.timeTemp = timerTemp;
            if (timerTemp == 0)
            {
                this.TimeLeft.Text = this.timeLeft.ToString();
                this.timeMutex.ReleaseMutex();
                Thread.Sleep(100);
            }
        }

        //private void getNewQuestion(object sender, DoWorkEventArgs e)
        //{            
        //    int questionsTemp = this.numQuestionsLeft;
        //    bool newQuestion = false;
        //    this.getQuestion();

        //    while(this.numQuestionsLeft != 0)
        //    {
        //        if (this.updatingThread.CancellationPending)
        //        {
        //            e.Cancel = true;
        //            break;
        //        }

        //        this.mtx.WaitOne();
                
        //        if(questionsTemp == this.numQuestionsLeft + 1)
        //        {
        //            wait = true;
        //            Thread.Sleep(3000);
        //            wait = false;
        //            this.updatingThread.ReportProgress(2, null);
        //            newQuestion = true;
        //        }
        //        if (this.timeTemp == 0)
        //        {
        //            this.numQuestionsLeft--;
        //            newQuestion = true;
        //        }
        //        if(this.numQuestionsLeft == 0)
        //        {
        //            break;
        //        }
        //        if(newQuestion)
        //        {
                    

        //            questionsTemp--;
        //            //restarting the time
        //            this.stopwatch.Restart();
        //            newQuestion = false;
        //        }

        //        this.mtx.ReleaseMutex();
        //        Thread.Sleep(1000);
        //    }
        //}

        private void getQuestion()
        {
            Stream.Send(new JObject(), Codes.GET_QUESTION);
            Response usersResponse = Stream.Recieve();

            if (Stream.Response(usersResponse, Codes.GET_QUESTION))
            {
                updateNewQuestion(usersResponse.jObject);
            }
        }

        private void resetColor(Button button)
        {
            button.Background = Brushes.LightGray;
        }

        private void updateNewQuestion(JObject question)
        {                    
            this.QuestionText.Text = question[Keys.question].ToString();
            this.Difficulty.Text = question[Keys.difficulty].ToString();
            this.Category.Text = question[Keys.category].ToString();

            JArray jArray = (JArray)question[Keys.answers];

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
            this.TimeLeft.Text = this.timeLeft.ToString();
        }

        private void gameCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            //opens new window
            Utils.OpenWindow(this, new Results());
        }
        
        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(Answer1, 0);
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(Answer2, 1);
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(Answer3, 2);
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(Answer4, 3);
        }

        private void AnswerQuestion(Button selectedButton, int index)
        {
            this.stopwatch.Stop();
            currentTime = Convert.ToInt32(this.stopwatch.ElapsedMilliseconds / 1000.0);

            if (!this.updatingThread.IsBusy)
            {
                this.updatingThread.RunWorkerAsync(new Tuple<Button, int>(selectedButton, index));
            }
        }

        private void UpdateQuestions(object sender, DoWorkEventArgs e)
        {
            Tuple<Button, int> param = (Tuple<Button, int>)e.Argument;
            int index = param.Item2;

            if (this.timeThread.CancellationPending)
            {
                e.Cancel = true;
                return;
            }

            this.timeMutex.WaitOne();

            JObject jObject = new JObject
            {
                [Keys.answerIndex] = index,
                [Keys.answerTime] = this.currentTime
            };
            Stream.Send(jObject, Codes.SUBMIT_ANSWER);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.SUBMIT_ANSWER))
            {
                this.updatingThread.ReportProgress(0, new Tuple<int, Button, int>(
                    Convert.ToInt32((string)response.jObject[Keys.correctAnswerIndex]), param.Item1, param.Item2));
            }

            this.timeMutex.ReleaseMutex();
        }

        private void UpdateThreadProgress(object sender, ProgressChangedEventArgs e)
        {
            Tuple<int, Button, int> param = (Tuple<int, Button, int>)e.UserState;
            int correctAnswerIndex = param.Item1;
            Button selectedButton = param.Item2;
            int index = param.Item3;

            if (correctAnswerIndex != index)
            {
                selectedButton.Background = Brushes.Red;
            }
            else
            {
                numCorrectanswers++;
            }
            Button correctButton = this.Answer1;
            switch (correctAnswerIndex)
            {
                case 0:
                    correctButton = this.Answer1;
                    break;
                case 1:
                    correctButton = this.Answer2;
                    break;
                case 2:
                    correctButton = this.Answer3;
                    break;
                case 3:
                    correctButton = this.Answer4;
                    break;
            }
            correctButton.Background = Brushes.Green;

            this.numQuestionsLeft--;

            Thread.Sleep(3000);

            this.resetColor(correctButton);
            this.resetColor(selectedButton);
            this.CorrectAnswers.Text = this.numCorrectanswers.ToString();
            this.AnswersLeft.Text = numQuestionsLeft.ToString();

            this.getQuestion();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            //dont forget to stop the thread here.
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
