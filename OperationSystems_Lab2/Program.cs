using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;

namespace Lab2OS
{
    class Program
    {
        public static bool ConnectToServer(Socket s, int x, char ch, int OurPort)
        {
            Console.WriteLine("Client Started");
            s.Connect("127.0.0.1", OurPort);
            Console.WriteLine("Client Connected to server " + ch);
            byte[] bytes = Encoding.ASCII.GetBytes(x.ToString());
            s.Send(bytes);
            byte[] ans = new byte[256];
            s.Receive(ans);
            Console.WriteLine("Server " + ch + " returned:" + " " + BitConverter.ToBoolean(ans).ToString());
            return BitConverter.ToBoolean(ans);
        }
        static Socket sockF = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        static Socket sockG = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        static int FPort = 1034;
        static int GPort = 1035;
        private static int X;
        static void Main(string[] args)
        {
            bool fres, gres;
            Console.WriteLine("Input x");
            X = int.Parse(Console.ReadLine());
            Task<bool> taskF = new Task<bool>(() => ConnectToServer(sockF, X, 'F', FPort));
            Task<bool> taskG = new Task<bool>(() => ConnectToServer(sockG, X, 'G', GPort));
            taskF.Start();
            taskG.Start();
            bool flag = true;
            while (flag)
            {
                Thread.Sleep(5000);
                Console.WriteLine("Print 1 (Stop) or 2 (Continue) or 3 (don't ask again) or 4 (change x)");
                int key = int.Parse(Console.ReadLine());
                switch (key)
                {
                    case 1:
                        flag = false;
                        break;
                    case 2:
                        if (taskF.IsCompleted && taskG.IsCompleted)
                        {
                            Console.WriteLine("Result of f||g using Sockets is " + (taskF.Result || taskG.Result));
                            flag = false;
                        }
                        break;

                    case 3:
                        Console.WriteLine("Result of f||g using Sockets is " + (taskF.Result || taskG.Result));
                        flag = false;
                        break;
                    case 4:
                        Console.WriteLine("Input new value of x");
                        X = int.Parse(Console.ReadLine());
                        goto case 2;
                }
            }
            Console.WriteLine("End of execution");
            Console.ReadKey();
        }
    }
}
