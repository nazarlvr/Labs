using System;
using System.Collections.Generic;
using System.IO;

namespace LAB3
{
    public class Converter
    {
        public static string GetString(int n)
        {
            string BinaryString = n.ToString();
            while (BinaryString.Length != 28)
                BinaryString = "0" + BinaryString;
            return BinaryString;
        }
        public static string CreateBinaryString(int n)
        {
            char[] arr = new char[28]; //28 bit long registers and stack
            int i = 0;
            int pos = 27;
            while (i < 28)
            {
                if ((n & (1 << i)) != 0)
                {
                    arr[pos] = '1';
                }
                else
                {
                    arr[pos] = '0';
                }

                i++;
                pos--;
            }

            string BinaryString = new string(arr);
            return BinaryString;
        }

        public static int GetRegisterIndex(string name)
        {
            return int.Parse(name[name.Length - 1].ToString());
        }
    }


    public class Parser
    {
        private string path = @"D:\AOC_KM\LAB3\lab3.txt";
        public List<Command> commands { get; private set; } = new List<Command>();

        public void CreateCommands()
        {
            StreamReader sr = File.OpenText(path);
            while(!sr.EndOfStream)
            {
                string commandString = sr.ReadLine();
                string[] OperationAndOperands = commandString.Split(' ');
                string operation = OperationAndOperands[0];
                string[] operands = OperationAndOperands[1].Split(',');

                commands.Add(new Command(operation, operands));
            }
        }
    }

    public class Command
    {
        public string Operation { get; set; }
        public string[] Operands { get; set; }

        public Command(string operation, string[] operands)
        {
            if(operation != "add" && operation != "invert")
                throw new ArgumentException("unknown command");
            Operation = operation;
            Operands = operands;
        }

    }
    
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Parser parser = new Parser();
                parser.CreateCommands();
                List<Command> commands = parser.commands;

                ProcessorWork processorWork = new ProcessorWork();
                foreach (Command com in commands)
                {
                    processorWork.ExecuteCommand(com);
                }
            }

            catch (ArgumentException ae)
            {
                Console.WriteLine("\n ArgException: " + ae.Message);
            }
            catch (OverflowException oe)
            {
                Console.WriteLine("\n OverFlowException: " + oe.Message);
            }
            catch (System.IO.IOException ioexcpt)
            {
                Console.WriteLine("\n OverFlowException: " + ioexcpt.Message);
            }
            finally
            {
                Console.WriteLine("\nEnd");
                Console.ReadKey();
            }
        }
    }
}
