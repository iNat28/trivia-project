﻿using Newtonsoft.Json.Linq;
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
    public partial class QuestionWindow : CustomWindow
    {
        private readonly Stopwatch stopwatch;
        private int numCorrectAnswers;
        private int numQuestionsLeft;
        private int timeLeft;
        private int timerTemp;
        private int selectedAnswerIndex;
        private bool answersAreDisplayed;
        private bool showResults;

        //mutex
        private readonly Mutex mutex;
        private double currentTime;

        //threads
        private readonly BackgroundWorker thread;

        private enum ThreadCodes
        {
            UPDATE_TIME,
            SUBMIT_ANSWER,
            GET_NEW_QUESTION
        };

        public QuestionWindow()
        {
            InitializeComponent();

            base.ErrorOutput = this.ErrorOutput;

            this.numCorrectAnswers = 0;
            this.numQuestionsLeft = 0;
            this.timeLeft = 0;
            this.timerTemp = 0;
            this.selectedAnswerIndex = -1;
            this.answersAreDisplayed = false;
            this.showResults = true;

            this.mutex = new Mutex();

            this.thread = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };

            this.stopwatch = new Stopwatch();

            this.thread.DoWork += WorkForThread;
            this.thread.ProgressChanged += UpdateThread;
            this.thread.RunWorkerCompleted += GameCompleted;
        }

        public override void OnShow(params object[] param)
        {
            int numQuestions = (int)param[0];
            int answerTime = (int)param[1];

            this.numCorrectAnswers = 0;
            this.currentTime = answerTime;
            this.numQuestionsLeft = numQuestions;
            this.CorrectAnswers.Text = "0";
            this.timeLeft = answerTime;
            this.timerTemp = this.timeLeft;
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.TimeLeft.Text = answerTime.ToString();
            this.selectedAnswerIndex = -1;
            this.answersAreDisplayed = false;
            this.showResults = true;

            this.GetQuestion();
            this.ResetAnswerColors();
            this.thread.RunWorkerAsync();
        }

        private void WorkForThread(object sender, DoWorkEventArgs e)
        {
            this.mutex.WaitOne();
            Thread.Sleep(1000);
            this.stopwatch.Start();
            while (true)
            {
                //Update time
                this.mutex.ReleaseMutex();
                this.thread.ReportProgress((int)ThreadCodes.UPDATE_TIME, null);
                Thread.Sleep(100);
                this.mutex.WaitOne();

                if (timerTemp == 0)
                {
                    //Makes sure the user can't press the buttons
                    this.answersAreDisplayed = true;
                    
                    //Submit the answer
                    this.mutex.ReleaseMutex();
                    this.thread.ReportProgress((int)ThreadCodes.SUBMIT_ANSWER, null);
                    Thread.Sleep(100);
                    this.mutex.WaitOne();

                    Thread.Sleep(3000);

                    if (this.numQuestionsLeft != 0)
                    {
                        this.mutex.ReleaseMutex();
                        //Get the next question
                        this.thread.ReportProgress((int)ThreadCodes.GET_NEW_QUESTION, null);
                        this.answersAreDisplayed = false;
                        Thread.Sleep(100);
                        this.mutex.WaitOne();

                        this.stopwatch.Restart();
                    }
                    else
                    {
                        this.thread.CancelAsync();
                    }
                }

                if (this.thread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                Thread.Sleep(900);
            }

            this.mutex.ReleaseMutex();
        }

        private void UpdateThread(object sender, ProgressChangedEventArgs e)
        {
            this.mutex.WaitOne();
            
            switch((ThreadCodes)e.ProgressPercentage)
            {
                case ThreadCodes.UPDATE_TIME:
                    ChangeTimeBox();
                    break;
                case ThreadCodes.SUBMIT_ANSWER:
                    SubmitAnswer();
                    break;
                case ThreadCodes.GET_NEW_QUESTION:
                    GetNewQuestion();
                    break;
            }
            
            this.mutex.ReleaseMutex();
        }

        private void ChangeTimeBox()
        {
            this.timerTemp = Convert.ToInt32(this.TimeLeft.Text);
            this.timerTemp--;
            this.TimeLeft.Text = this.timerTemp.ToString();
        }

        private void GetQuestion()
        {
            Stream.Send(new JObject(), Codes.GET_QUESTION);
            Response usersResponse = Stream.Recieve();

            if (Stream.Response(usersResponse, Codes.GET_QUESTION))
            {
                UpdateNewQuestion(usersResponse.jObject);
            }
        }

        private void ResetAnswerColors()
        {            
            for(int i = 0; i < 4; i++)
            {
                this.GetAnswerButtonFromIndex(i).Background = Brushes.LightGray;
            }
        }

        private void UpdateNewQuestion(JObject question)
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

        private void GameCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (this.showResults)
            {
                WindowManager.OpenWindow(WindowTypes.RESULT);
            }
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
            if (!answersAreDisplayed && this.selectedAnswerIndex != index)
            {
                this.ResetAnswerColors();
                this.currentTime = this.stopwatch.ElapsedMilliseconds / 1000.0;
                this.selectedAnswerIndex = index;
                
                Button selectedButton = this.GetAnswerButtonFromIndex(index);
                selectedButton.Background = Brushes.LightBlue;
                
                this.SelectedAnswerOutput.Text = (string)selectedButton.Content;
                this.TimeTookForAnswerOutput.Text = this.currentTime.ToString("0.00");
            }
        }

        private void SubmitAnswer()
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
                
                if (this.selectedAnswerIndex != -1)
                {
                    if (correctAnswerIndex != this.selectedAnswerIndex)
                    {
                        this.GetAnswerButtonFromIndex(this.selectedAnswerIndex).Background = Brushes.Red;
                    }
                    else
                    {
                        numCorrectAnswers++;
                    }
                }
                else
                {
                    this.TimeTookForAnswerOutput.Text = this.currentTime.ToString();
                }
                
                Button correctButton = this.GetAnswerButtonFromIndex(correctAnswerIndex);
                correctButton.Background = Brushes.Green;

                this.numQuestionsLeft--;
            }
        }

        private void GetNewQuestion()
        {
            this.ResetAnswerColors();

            this.CorrectAnswers.Text = this.numCorrectAnswers.ToString();
            this.AnswersLeft.Text = numQuestionsLeft.ToString();
            this.TimeLeft.Text = this.timeLeft.ToString();
            this.SelectedAnswerOutput.Text = "";
            this.TimeTookForAnswerOutput.Text = "";
            this.selectedAnswerIndex = -1;
            this.currentTime = this.timeLeft;

            this.GetQuestion();
        }

        private Button GetAnswerButtonFromIndex(int index)
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
            this.LeaveGame();
        }

        protected override void OnClosed(EventArgs e)
        {
            if (LogoutWindow.toClose)
            {
                LeaveGame();
            }
        }

        private void LeaveGame()
        {
            this.stopwatch.Stop();
            this.showResults = false;
            this.thread.CancelAsync();

            Stream.Send(new JObject(), Codes.LEAVE_GAME);
            Stream.Response(Stream.Recieve(), Codes.LEAVE_GAME);
            WindowManager.OpenWindow(WindowTypes.MAIN);
        }
    }
}
