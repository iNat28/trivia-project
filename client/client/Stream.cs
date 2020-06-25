﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Net.Sockets;
using System.Net;
using Newtonsoft.Json.Bson;
using Newtonsoft.Json.Linq;
using System.IO;

namespace client
{
    public struct Response
    {
        public JObject jObject;
        public Codes code;
    }

    public static class Stream
    {
        private static TcpClient tcpClient;
        private static NetworkStream client;

        private const int MSG_CODE_SIZE = 1;
        private const int MSG_LEN_SIZE = 4;
        private const string IP_ADDRESS = "127.0.0.1";
        private const int PORT = 40200;

        public static NetworkStream Client
        {
            get
            {
                if (client == null)
                {
                    try
                    {
                        tcpClient = new TcpClient();
                        tcpClient.Connect(new IPEndPoint(IPAddress.Parse(IP_ADDRESS), PORT));
                        client = tcpClient.GetStream();
                    }
                    catch(Exception e)
                    {
                        User.PrintError(e);
                    }
                }

                return client;
            }
        }

        public static void Close()
        {
            try
            {
                client.Close();
                tcpClient = null;
                client = null;
            }
            catch (Exception e)
            {
                User.PrintError(e);
            }
        }

        public static void Signout()
        {
            JObject jObject = new JObject
            {
                ["username"] = User.username
            };
            Send(jObject, Codes.LOGOUT);
            Recieve();
        }

        public static void Send(JObject jObject, Codes code)
        {
            try
            {
                MemoryStream memoryStream = new MemoryStream();
                BsonDataWriter bsonWriter = new BsonDataWriter(memoryStream);
                jObject.WriteTo(bsonWriter);

                byte[] buffer = new byte[] { Convert.ToByte(code) };
                Client.Write(buffer, 0, buffer.Length);
                Client.Write(memoryStream.ToArray(), 0, (int)memoryStream.Length);
                Client.Flush();
            }
            catch (Exception e)
            {
                User.PrintError(e);
            }
        }

        public static Response Recieve()
        {
            Response response = new Response();
            try
            {
                int bufferSize;
                byte[] bufferBson;
                byte[] bufferRead = new byte[MSG_CODE_SIZE + MSG_LEN_SIZE];

                Client.Read(bufferRead, 0, bufferRead.Length);
            
                //Converts the read buffer to the message code and size
                //If buffer code size is changed, then this needs to be changed
                response.code = (Codes)bufferRead[0]; 
                bufferSize = BitConverter.ToInt32(bufferRead, MSG_CODE_SIZE);

                bufferBson = new byte[bufferSize + MSG_LEN_SIZE];
                //Copies the Bson length to the bson buffer
                Array.Copy(bufferRead, MSG_CODE_SIZE, bufferBson, 0, MSG_LEN_SIZE);

                Client.Read(bufferBson, MSG_LEN_SIZE, bufferBson.Length - MSG_LEN_SIZE);

                response.jObject = (JObject)JToken.ReadFrom(new BsonDataReader(new MemoryStream(bufferBson)));
            }
            catch (Exception e)
            {
                User.PrintError(e);
            }

            return response;
        }

        public static bool Response(Response response, Codes code, TextBlock errorOutput)
        {
            string error = "";

            try
            {
                if (response.code == code)
                {
                    return true;
                }
                
                if (response.code == Codes.ERROR_CODE)
                {
                    error = (string)response.jObject["message"];
                }
                else
                {
                    error = response.jObject.ToString();
                }

                errorOutput.Text = error;
            }
            catch (Exception e)
            {
                User.PrintError(e);
            }

            return false;
        }
    }
}
