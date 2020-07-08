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
        private int timerTemp;
        private int selectedAnswerIndex;
        private bool wait = false;
        //mutex
        private Mutex mtx;
        private int currentTime;

        //threads
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
            this.timerTemp = this.timeLeft;
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.TimeLeft.Text = answerTime.ToString();
            //creating the stopwatch
            this.stopwatch = new Stopwatch();
                        

            //starting threads
            this.mtx = new Mutex();
            //this.timeMutex = new Mutex();

            //this.updatingThread = new BackgroundWorker
            //{
            //    WorkerReportsProgress = true,
            //    WorkerSupportsCancellation = true
            //};

            this.timeThread = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            this.getQuestion();

            //this.updatingThread.DoWork += UpdateQuestions;
            //this.updatingThread.ProgressChanged += UpdateThreadProgress;
            //this.updatingThread.RunWorkerCompleted += gameCompleted;

            this.timeThread.DoWork += updateTime;
            this.timeThread.ProgressChanged += updateThread;
            this.timeThread.RunWorkerCompleted += gameCompleted;
            this.timeThread.RunWorkerAsync();

            this.stopwatch.Start();
        }

        private void updateTime(object sender, DoWorkEventArgs e)
        {
            this.mtx.WaitOne();
            while (true)
            {
                //Update time
                this.mtx.ReleaseMutex();
                this.timeThread.ReportProgress(0, null);
                Thread.Sleep(100);
                this.mtx.WaitOne();

                if (timerTemp == 0)
                {
                    //this.mtx.ReleaseMutex();
                    //Submit the answer
                    this.mtx.ReleaseMutex();
                    this.timeThread.ReportProgress(1, null);
                    Thread.Sleep(100);
                    this.mtx.WaitOne();

                    if (this.numQuestionsLeft != 0)
                    {
                        Thread.Sleep(3000);

                        this.mtx.ReleaseMutex();
                        //Get the next question
                        this.timeThread.ReportProgress(2, null);
                        Thread.Sleep(100);
                        this.mtx.WaitOne();

                        this.stopwatch.Restart();
                    }
                    else
                    {
                        this.timeThread.CancelAsync();
                    }
                }

                if (this.timeThread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                Thread.Sleep(900);
            }

            this.mtx.ReleaseMutex();
        }

        private void updateThread(object sender, ProgressChangedEventArgs e)
        {
            this.mtx.WaitOne();
            switch(e.ProgressPercentage)
            {
                case 0:
                    changeTimeBox();
                    break;
                case 1:
                    UpdateQuestion();
                    break;
                case 2:
                    GetNewQuestion();
                    break;
            }
            this.mtx.ReleaseMutex();
        }

        private void changeTimeBox()
        {
            this.timerTemp = Convert.ToInt32(this.TimeLeft.Text);
            this.timerTemp--;
            this.TimeLeft.Text = this.timerTemp.ToString();
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
            this.AnswerQuestion(0);
        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(1);
        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(2);
        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            this.AnswerQuestion(3);
        }

        private void AnswerQuestion(int index)
        {
            if (!wait && this.selectedAnswerIndex != index)
            {                
                this.currentTime = Convert.ToInt32(this.stopwatch.ElapsedMilliseconds / 1000.0);
                this.selectedAnswerIndex = index;
                Button selectedButton = this.getAnswerButtonFromIndex(index);
                selectedButton.Background = Brushes.LightGreen;
                this.SelectedAnswerOutput.Text = (string)selectedButton.Content;
                this.TimeTookForAnswerOutput.Text = this.currentTime.ToString();
            }
        }

        private void UpdateQuestion()
        {
            JObject jObject = new JObject
            {
                [Keys.answerIndex] = this.selectedAnswerIndex,
                [Keys.answerTime] = this.currentTime
            };
            Stream.Send(jObject, Codes.SUBMIT_ANSWER);

            Response response = Stream.Recieve();

            if (Stream.Response(response, Codes.SUBMIT_ANSWER))
            {
                int correctAnswerIndex = (int)response.jObject[Keys.correctAnswerIndex];
                Button selectedButton = this.getAnswerButtonFromIndex(this.selectedAnswerIndex);

                if (correctAnswerIndex != this.selectedAnswerIndex)
                {
                    selectedButton.Background = Brushes.Red;
                }
                else
                {
                    numCorrectanswers++;
                }
                Button correctButton = this.getAnswerButtonFromIndex(correctAnswerIndex);
                correctButton.Background = Brushes.Green;

                this.numQuestionsLeft--;
            }
            //this.mtx.ReleaseMutex();
        }

        private void GetNewQuestion()
        {
            for(int i = 0; i < 4; i++)
            {
                this.resetColor(this.getAnswerButtonFromIndex(i));
            }

            this.CorrectAnswers.Text = this.numCorrectanswers.ToString();
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.TimeLeft.Text = this.timeLeft.ToString();

            this.getQuestion();
        }

        private Button getAnswerButtonFromIndex(int index)
        {
            switch (index)
            {
                case 0:
                    return this.Answer1;
                case 1:
                    return this.Answer2;
                case 2:
                    return this.Answer3;
                case 3:
                    return this.Answer4;
                default:
                    throw new IndexOutOfRangeException();
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            this.stopwatch.Stop();
            this.timeThread.CancelAsync();
            Utils.OpenWindow(this, new MainWindow());
        }
    }
}
