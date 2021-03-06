using System.Net;
using System.Net.Sockets;
using System.Text;

namespace ServerF
{
    class Program
    {
        public static bool g(int x)
        {
            bool res = x < 0 || (x>0 && x%5 == 0) ;
            Thread.Sleep(7000);
            if (x > 20 && x < 30)
            {
                Thread.Sleep(100000);
                return false;
            }
            return res;
        }

        static int OurPort = 1035;
        static void Send(string message, Socket temp)
        {
            byte[] data = Encoding.Unicode.GetBytes(message);
            temp.Send(data);
        }

        static void Main(string[] args)
        {
            try
            {
                Socket listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                Console.WriteLine("Server started");
                listenSocket.Bind(new IPEndPoint(IPAddress.Any, OurPort));
                listenSocket.Listen(1);
                Socket temperary = listenSocket.Accept();
                string s = "";
                bool flag = true;
                while (flag)
                {
                    Console.WriteLine("New Connection");
                    byte[] bytes = new byte[256];
                    int len = temperary.Receive(bytes);
                    s = Encoding.ASCII.GetString(bytes, 0, len);
                    int x = Int32.Parse(s);
                    Console.WriteLine(DateTime.Now.ToShortTimeString() + " " + s);
                    bool answer = g(x);
                    byte[] ans = new byte[256];
                    ans = BitConverter.GetBytes(answer);
                    temperary.Send(ans);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadKey(true);
        }
    }
}
