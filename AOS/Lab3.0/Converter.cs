
using System;
using System.Linq;

namespace Lab3._0
{
    internal class Converter
    {

        public static string GetString(int n)
        {
            string joinedBinaryStr = Convert.ToString(n);
            while (joinedBinaryStr.Length != 20) { joinedBinaryStr = "0" + joinedBinaryStr; }
            string separatedBinaryStr = SeparateString(joinedBinaryStr);
            return separatedBinaryStr;
        }

        public static string GetBinaryString(int n)
        {
            char[] b = new char[20]; // 20 bytes long adress
            int pos = 19;
            int i = 0;

            while (i < 20)
            {
                if ((n & (1 << i)) != 0)
                {
                    b[pos] = '1';
                }
                else
                {
                    b[pos] = '0';
                }
                pos--;
                i++;
            }
            string joinedBinaryStr = new string(b);
            string separatedBinaryStr = SeparateString(joinedBinaryStr);
            return separatedBinaryStr;
        }

        public static string SeparateString(string str)
        {
            const int separateOnLength = 4;

            string separated = new string(
                str.Select((x, i) => i > 0 && i % separateOnLength == 0 ? new[] { ' ', x } : new[] { x })
                    .SelectMany(x => x)
                    .ToArray()
                );
            return separated;
        }

        public static int GetIndexOfRegister(string name)
        {
            return int.Parse(name[name.Length - 1].ToString());
        }
    }
}