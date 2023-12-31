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
        private int timePerQuestion;
        private int timerTemp;
        private int selectedAnswerIndex;
        private bool answersAreDisplayed;
        private bool showResults;

        //mutex
        private Mutex mutex;
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

            this.numCorrectAnswers = 0;
            this.numQuestionsLeft = 0;
            this.timePerQuestion = 0;
            this.timerTemp = 0;
            this.selectedAnswerIndex = -1;
            this.answersAreDisplayed = false;
            this.showResults = true;

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

            this.mutex?.Close();
            this.mutex = new Mutex();

            this.numCorrectAnswers = 0;
            this.currentTime = answerTime;
            this.numQuestionsLeft = numQuestions;
            this.UpdateRightTextBlock(numQuestions);
            this.UpdateSelectedAnswer();
            this.timePerQuestion = answerTime;
            this.timerTemp = this.timePerQuestion;
            this.selectedAnswerIndex = -1;
            this.answersAreDisplayed = false;
            this.showResults = true;

            this.GetQuestion();
            this.stopwatch.Restart();
            this.ResetAnswerColors();
            this.thread.RunWorkerAsync();
        }

        public override TextBlock GetErrorOutput()
        {
            return this.ErrorOutput;
        }

        private void WorkForThread(object sender, DoWorkEventArgs e)
        {
            this.mutex.WaitOne();
            Thread.Sleep(1000);

            this.timerTemp = this.timePerQuestion;
            while (true)
            {
                if (this.thread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                //Update time
                this.mutex.ReleaseMutex();
                this.thread.ReportProgress((int)ThreadCodes.UPDATE_TIME, null);
                Thread.Sleep(100);
                this.mutex.WaitOne();

                if (this.thread.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                if (this.timerTemp == 0)
                {
                    //Makes sure the user can't press the buttons
                    this.answersAreDisplayed = true;
                    
                    //Submit the answer
                    this.mutex.ReleaseMutex();
                    this.thread.ReportProgress((int)ThreadCodes.SUBMIT_ANSWER, null);
                    Thread.Sleep(100);
                    this.mutex.WaitOne();

                    Thread.Sleep(500);
                    if (this.thread.CancellationPending)
                    {
                        e.Cancel = true;
                        break;
                    }
                    Thread.Sleep(2000);

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
                        e.Cancel = true;
                        break;
                    }
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
            this.timerTemp--;
            UpdateTimeLeft(this.timerTemp);
        }

        private void GetQuestion()
        {
            Response usersResponse = Stream.Send(Codes.GET_QUESTION);

            if (Stream.Response(usersResponse, Codes.GET_QUESTION))
            {
                UpdateNewQuestion(usersResponse.jObject);
            }
            else
            {
                this.thread.CancelAsync();
            }
        }

        protected override Border GetBorder()
        {
            return this.Border;
        }

        private void ResetAnswerColors()
        {            
            for(int i = 0; i < 4; i++)
            {
                this.GetAnswerButtonFromIndex(i).Background = Brushes.CornflowerBlue;
            }
        }

        private void UpdateNewQuestion(JObject question)
        {
            this.QuestionText.Text = question[Keys.question].ToString();
            this.LeftTextBlock.Text =
                "Difficulty: " + this.GetDifficulty((int)question[Keys.difficulty]) +
                "\nCategory:\n" + (string)question[Keys.category];

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

            this.UpdateTimeLeft(this.timePerQuestion);
        }

        private string GetDifficulty(int difficulty)
        {
            switch(difficulty)
            {
                case 1:
                    return "Easy";
                case 3:
                    return "Hard";
                default:
                    return "Medium";
            }
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
                selectedButton.Background = Brushes.RoyalBlue;

                this.UpdateSelectedAnswer((string)selectedButton.Content, this.currentTime);
            }
        }

        private void SubmitAnswer()
        {
            JObject jObject = new JObject
            {
                [Keys.answerIndex] = this.selectedAnswerIndex,
                [Keys.answerTime] = this.currentTime
            };
            Response response = Stream.Send(jObject, Codes.SUBMIT_ANSWER);

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
                    this.UpdateSelectedAnswer("", this.currentTime);
                }
                
                Button correctButton = this.GetAnswerButtonFromIndex(correctAnswerIndex);
                correctButton.Background = Brushes.MediumSeaGreen;

                this.numQuestionsLeft--;
            }
            else
            {
                this.thread.CancelAsync();
            }
        }

        private void UpdateRightTextBlock(int answersLeft = 0, int correctAnswers = 0)
        {
            this.RightTextBlock.Text =
                Utils.GetProperString(answersLeft, "Answer") + " Left\n" +
                Utils.GetProperString(correctAnswers, "Correct Answer");
        }

        private void UpdateSelectedAnswer(string selectedAnswer = "", double timeTook = -1)
        {
            this.SelectedAnswer.Text =
                "Selected Answer:\n" +
                selectedAnswer +
                "\nTime took for answer:\n";
            
            if(timeTook >= 0)
            {
                this.SelectedAnswer.Text += Utils.GetProperString(timeTook);
            }
        }

        private void UpdateTimeLeft(int timeLeft)
        {
            this.TimeLeft.Text = Utils.GetProperString(timeLeft, "second") + " left";
        }

        private void GetNewQuestion()
        {
            this.ResetAnswerColors();

            this.UpdateRightTextBlock(this.numQuestionsLeft, this.numCorrectAnswers);
            this.UpdateTimeLeft(this.timePerQuestion);
            this.UpdateSelectedAnswer();
            this.selectedAnswerIndex = -1;
            this.currentTime = this.timePerQuestion;
            this.timerTemp = this.timePerQuestion;

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

        protected override void OnClosing(CancelEventArgs e)
        {
            if (!WindowManager.exit)
            {
                base.OnClosing(e);
                LeaveGame();
            }
        }

        private void LeaveGame()
        {
            this.stopwatch.Stop();
            this.showResults = false;

            if (Stream.Response(Stream.Send(Codes.LEAVE_GAME), Codes.LEAVE_GAME))
            {
                this.thread.CancelAsync();

                WindowManager.OpenWindow(WindowTypes.MAIN);
            }
        }
    }
}
