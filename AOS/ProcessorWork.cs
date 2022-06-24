using System;
using System.Collections.Generic;
using System.Text;

namespace LAB3
{
    class ProcessorWork
    {
        public ProcessorState CurrentState = new ProcessorState();
        
        public void ExecuteCommand(Command com)
        {
            Tact1(com);
            PrintCurrentState();
            NextOrStop();
            Tact2(com);
            PrintCurrentState();
            NextOrStop();
            Tact3(com);
            PrintCurrentState();
            NextOrStop();
        }

        private void Tact1(Command com)
        {
            CurrentState.Command = com.Operation + " " + string.Join(",", com.Operands);
            string BinaryInitValue = Converter.GetString(int.Parse(com.Operands[1]));
            switch (com.Operation)
            {
                case "invert":
                    CurrentState.Ins = com.Operation + " | " + com.Operands[0] + " | " + com.Operands[1];
                    break;
                case "add":
                    CurrentState.Ins = com.Operation + " | " + com.Operands[0] + " | " + BinaryInitValue;
                    break;
            }

            ++CurrentState.PC;
            CurrentState.TC = 1;
        }

        private void Tact2(Command com)
        {
            int registerIndex = Converter.GetRegisterIndex(com.Operands[0]);
            int WorkValue = int.Parse(com.Operands[1]);
            string BinaryInitValue;

            switch(com.Operation)
            {
                case "add":
                    BinaryInitValue = Converter.GetString(WorkValue);
                    CurrentState.Registers[registerIndex] = BinaryInitValue;

                    CurrentState.PS = int.Parse(BinaryInitValue[0].ToString());
                    break;
                case "invert":

                    CurrentState.Stack[4] = CurrentState.Stack[3];
                    CurrentState.Stack[3] = CurrentState.Stack[2];
                    CurrentState.Stack[2] = CurrentState.Stack[1];
                    CurrentState.Stack[1] = CurrentState.Stack[0];
                    CurrentState.Stack[0] = CurrentState.Registers[registerIndex];

                    CurrentState.PS = int.Parse(CurrentState.Stack[0][0].ToString());
                    break;
            }

            CurrentState.TC = 2;
        }

        private void Tact3(Command com)
        {
            int registerIndex = Converter.GetRegisterIndex(com.Operands[0]);
            string WorkValue;
            WorkValue = com.Operands[1];

            switch(com.Operation)
            {
                case "invert":
                    Invert(WorkValue);

                    CurrentState.PS = int.Parse(CurrentState.Stack[0][0].ToString());
                    break;
            }

            CurrentState.TC = 3;
        }

        private void NextOrStop()
        {
            Console.Write("Press C to continue");
            char pb = Console.ReadKey().KeyChar;
            if (pb != 'C' && pb != 'c')
                throw new System.IO.IOException("Press correct button");

            Console.WriteLine("");
            Console.WriteLine("");

        }

        private void PrintCurrentState()
        {
            Console.WriteLine($"Command = {CurrentState.Command}");
            Console.WriteLine($"StackTop = {CurrentState.Stack[0]} Ins = {CurrentState.Ins}");
            Console.WriteLine($"R0 = {CurrentState.Registers[0]} PC = {CurrentState.PC}");
            Console.WriteLine($"R1 = {CurrentState.Registers[1]} TC = {CurrentState.TC}");
            Console.WriteLine($"R2 = {CurrentState.Registers[2]} PS = {CurrentState.PS}");
            Console.WriteLine("");
        }

        private void Invert(string workValue)
        {
            if (workValue == "1")
            {
                StringBuilder StackValue = new StringBuilder(CurrentState.Stack[0]);
                for (int i = 27; i >= 0; i--)
                {
                    if (i % 2 == 0)
                    {
                        if (StackValue[i] == '1')
                            StackValue[i] = '0';
                        else
                            StackValue[i] = '1';
                    }
                }

                CurrentState.Stack[0] = StackValue.ToString();
            }
            else if (workValue == "0")
            {
                StringBuilder StackValue = new StringBuilder(CurrentState.Stack[0]);
                for (int i = 27; i >= 0; i--)
                {
                    if (i % 2 == 1)
                    {
                        if (StackValue[i] == '1')
                            StackValue[i] = '0';
                        else
                            StackValue[i] = '1';
                    }
                }

                CurrentState.Stack[0] = StackValue.ToString();
            }
            else
                throw new ArgumentException("incorrect operand");
        }

    }
}
