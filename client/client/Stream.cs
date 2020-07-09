using System;
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
    public class Response
    {
        public JObject jObject;
        public Codes code;

        public Response(JObject jObject, Codes code)
        {
            this.jObject = jObject;
            this.code = code;
        }
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
                    tcpClient = new TcpClient();
                    tcpClient.Connect(new IPEndPoint(IPAddress.Parse(IP_ADDRESS), PORT));
                    client = tcpClient.GetStream();
                }

                return client;
            }
        }

        public static void Close()
        {
            WindowManager.OpenWindow(WindowTypes.LOGIN);

            client?.Close();
            tcpClient = null;
            client = null;

            WindowManager.PrintError("Error connecting to back end");
        }

        public static void Signout()
        {
            JObject jObject = new JObject
            {
                ["username"] = User.username
            };
            Send(jObject, Codes.LOGOUT);
        }

        public static Response Send(JObject jObject, Codes code)
        {
            MemoryStream memoryStream = new MemoryStream();
            BsonDataWriter bsonWriter = new BsonDataWriter(memoryStream);
            jObject.WriteTo(bsonWriter);
            byte[] buffer = new byte[] { Convert.ToByte(code) };

            try
            {
                Client.Write(buffer, 0, buffer.Length);
                Client.Write(memoryStream.ToArray(), 0, (int)memoryStream.Length);
                Client.Flush();
            }
            catch
            {
                Stream.Close();
                return null;
            }

            return Recieve();
        }

        public static Response Send(Codes code)
        {
            byte[] buffer = new byte[5];
            buffer[0] = Convert.ToByte(code);

            try
            {
                Client.Write(buffer, 0, buffer.Length);
            }
            catch
            {
                Stream.Close();
                return null;
            }

            return Recieve();
        }

        private static Response Recieve()
        {
            int bufferSize;
            byte[] bufferBson;
            byte[] bufferRead = new byte[MSG_CODE_SIZE + MSG_LEN_SIZE];

            try
            {
                Client.Read(bufferRead, 0, bufferRead.Length);
            }
            catch
            {
                Stream.Close();
                return null;
            }

            //Converts the read buffer to the message code and size
            Response response = new Response(null, (Codes)bufferRead[0]);

            //If buffer code size is changed, then this needs to be changed
            bufferSize = BitConverter.ToInt32(bufferRead, MSG_CODE_SIZE);

            if (bufferSize > 0)
            {
                bufferBson = new byte[bufferSize + MSG_LEN_SIZE];
                //Copies the Bson length to the bson buffer
                Array.Copy(bufferRead, MSG_CODE_SIZE, bufferBson, 0, MSG_LEN_SIZE);

                Client.Read(bufferBson, MSG_LEN_SIZE, bufferBson.Length - MSG_LEN_SIZE);

                response.jObject = (JObject)JToken.ReadFrom(new BsonDataReader(new MemoryStream(bufferBson)));
            }

            return response;
        }

        public static bool Response(Response response, Codes code)
        {
            try
            {
                return ResponseWithoutTryCatch(response, code);
            }
            catch (Exception e)
            {
                if (e.Message != "exit")
                {
                    WindowManager.PrintError(e);
                }
            }

            return false;
        }

        public static bool ResponseForThread(Response response, Codes code, out string error)
        {
            error = "";

            try
            {
                return ResponseWithoutTryCatch(response, code);
            }
            catch (Exception e)
            {
                error = e.Message;
            }

            return false;
        }

        private static bool ResponseWithoutTryCatch(Response response, Codes code)
        {
            string error;

            if (response == null)
            {
                error = "exit";
            }
            else if (response.code == code)
            {
                return true;
            }
            else if (response.code == Codes.ERROR_CODE)
            {
                error = (string)response.jObject["message"];
            }
            else
            {
                error = response.jObject.ToString();
            }

            throw new Exception(error);
        }
    }
}
