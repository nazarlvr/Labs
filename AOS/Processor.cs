using System;
using System.Collections.Generic;
using System.Text;

namespace LAB3
{
     class ProcessorState
    {
        public string Command { get; set; }
        public string Ins { get; set; }
        public string[] Stack { get; set; }    //STACK
        public string[] Registers { get; set; }   //registers
        public int PC { get; set; } //commands
        public int TC { get; set; } //tacts
        public int PS { get; set; } //status register

        public ProcessorState()
        {
            Command = string.Empty;
            Ins = string.Empty;
            PC = 0;
            TC = 0;
            PS = 0;

            System.Random random = new System.Random();
            Stack = new string[5];
            Registers = new string[3];
            for(int i = 0; i < Registers.Length;i++)
            {
                Registers[i] = Converter.CreateBinaryString(random.Next(127));
            }

            Stack[0] = Converter.CreateBinaryString(random.Next(127));
        }
    }
}
