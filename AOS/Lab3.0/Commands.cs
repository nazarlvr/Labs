using System;
using System.Linq;

namespace Lab3._0
{
    internal class Command
    {
        public string Operation { get; private set; }
        public string[] Operands { get; private set; }
        public Command(string operation, string[] operands)
        {
            if (operation != "repl" && operation != "add" && operation != "chg") { throw new ArgumentException("Unknown command"); }
            if (operands.Length != 3 && operands.Length != 2) { throw new ArgumentException("Number of operands is incorrect"); }
            Operation = operation;
            Operands = operands;
        }
    }
}