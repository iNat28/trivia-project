using Newtonsoft.Json.Linq;
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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private int roomId;
        
        public JoinRoom()
        {
            InitializeComponent();
            User.errorOutput = this.ErrorBox;

            Stream.Send(new JObject(), Codes.GET_ROOM);

            Response response = Stream.Recieve();

            //TODO Remove third param from Response
            if (Stream.Response(response, Codes.GET_ROOM))
            {
                JArray jArray = (JArray)response.jObject[Keys.rooms];
                foreach (JObject jObject in jArray)
                {
                    this.RoomsList.Items.Add(jObject[Keys.name]);
                }
            }
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.RoomsList.SelectedItem != null)
            {
                JObject jObject = new JObject
                {
                    ["roomId"] = this.roomId               
                };
                Stream.Send(jObject, Codes.JOIN_ROOM);

                Response response = Stream.Recieve();
                
                if (Stream.Response(response, Codes.JOIN_ROOM))
                {
                    Utils.OpenWindow(this, new Room(false, this.RoomsList.SelectedItem.ToString(), 0, 0));
                }          
            }
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Utils.OpenWindow(this, new MainWindow());
        }

        private void RoomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Stream.Send(new JObject(), Codes.GET_ROOM);

            Response response = Stream.Recieve();
            
            if (Stream.Response(response, Codes.GET_ROOM))
            {
                JArray jArray = (JArray)response.jObject[Keys.rooms];
                foreach (JObject jObject in jArray)
                {
                    if (jObject[Keys.name].ToString() == RoomsList.SelectedItem.ToString())
                        this.roomId = Convert.ToInt32(jObject[Keys.id].ToString());
                }
            }

        }
    }
}
