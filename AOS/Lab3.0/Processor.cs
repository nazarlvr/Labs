    using System;
using System.Linq;
using System.Text;

namespace Lab3._0
{
    internal class Processor
    {
        public ProcessorGenerate _ProcCurState = new ProcessorGenerate();

        public void ExecuteCommand(Command com)
        {
            Tact1(com);
            PrintCurrState();
            NextOrStop();
            Tact2(com);
            PrintCurrState();
            NextOrStop();
            Tact3(com);
            PrintCurrState();
            NextOrStop();
        }

        private void Tact1(Command com)
        {
            _ProcCurState.Command = com.Operation + ' ' + string.Join(",", com.Operands);

            string binaryInitVal = Converter.GetString(int.Parse(com.Operands[1]));
            switch (com.Operation)
            {
                case "repl":
                    _ProcCurState.Ins = com.Operation + " | " + com.Operands[0] + " | " + binaryInitVal + " | " + com.Operands[2];
                    break;
                case "add":
                    _ProcCurState.Ins = com.Operation + " | " + com.Operands[0] + " | " + binaryInitVal;
                    break;
                case "chg":
                    _ProcCurState.Ins = com.Operation + " | " + com.Operands[0] + " | " + com.Operands[1];
                    break;
            }
            
            ++_ProcCurState.PC;
            _ProcCurState.TC = 1;
        }

        private void Tact2(Command com)
        {
            int registerIndex = Converter.GetIndexOfRegister(com.Operands[0]);
            int workVal = int.Parse(com.Operands[1]);
            string binaryInitVal;

            switch (com.Operation)
            {
                case "repl":
                    binaryInitVal = Converter.GetString(workVal);
                    _ProcCurState.R[registerIndex] = binaryInitVal;
                    break;
                case "add":
                    binaryInitVal = Converter.GetString(workVal);
                    _ProcCurState.R[registerIndex] = binaryInitVal;
                    break;
            }
            

            _ProcCurState.TC = 2;
        }

        private void Tact3(Command com)
        {
            int registerIndex = Converter.GetIndexOfRegister(com.Operands[0]);
            string workVal;
            try
            {
                workVal = com.Operands[2];
            }
            catch (Exception) { workVal = com.Operands[1]; }
            switch (com.Operation)
            {
                case "repl":
                    Repl(registerIndex, workVal);
                    break;
                case "chg":
                    Repl(registerIndex, workVal);
                    break;
            }

            _ProcCurState.TC = 3;
        }

        private void Repl(int registerIndex, string moveVal)
        {
            string joinedBinaryStr = _ProcCurState.R[registerIndex].Replace(" ","");
            StringBuilder modReg = new StringBuilder(joinedBinaryStr);
            for (int i = 0; i < modReg.Length; i += 2)
            {
                if (modReg[i] == moveVal[0])
                {
                    char x = modReg[i];
                    modReg[i] = modReg[i + 1];
                    modReg[i + 1] = x;
                }
            }
            _ProcCurState.R[registerIndex] = Converter.SeparateString(modReg.ToString());
        }
        private void NextOrStop()
        {
            Console.Write("Press C to continue:");
            char pf = Console.ReadKey().KeyChar;
            if (pf != 'C' && pf != 'c')
            {
                throw new System.IO.IOException("Escape character has been used!");
            }
            Console.WriteLine("");
            Console.WriteLine("");
        }
        private void PrintCurrState()
        {
            Console.WriteLine($"Command = {_ProcCurState.Command}");
            Console.WriteLine($"R0 = {_ProcCurState.R[0]}  Ins = {_ProcCurState.Ins}");
            Console.WriteLine($"R1 = {_ProcCurState.R[1]}  PC = {_ProcCurState.PC}");
            Console.WriteLine($"R2 = {_ProcCurState.R[2]}  TC = {_ProcCurState.TC}");
            Console.WriteLine($"R3 = {_ProcCurState.R[3]} ");
            Console.WriteLine("");
        }
    }
}