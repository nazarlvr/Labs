using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Lab4OS
{
    class Lab4_23
    {
        public static int[] unitedcell = new int[3];

        private static void f1()
        {
            for (int i = 0; i < 50000; ++i)
            //lock (unitedcell)
            {
                unitedcell[0] = unitedcell[0] + 1;
                unitedcell[0] = unitedcell[0] + 1;
                unitedcell[1] = unitedcell[1] + 1;
                unitedcell[1] = unitedcell[1] + 1;
            }
        }

        private static void f2()
        {
            for (int i = 0; i < 50000; ++i)
            //lock (unitedcell)
            {
                unitedcell[2] = unitedcell[2] + 1;
                unitedcell[2] = unitedcell[2] + 1;
                unitedcell[1] = unitedcell[1] + 1;
                unitedcell[1] = unitedcell[1] + 1;
            }
        }

        public static void Main()
        {
            Task t1 = new Task(f1);
            Task t2 = new Task(f2);
            t1.Start();
            t2.Start();
            t1.Wait();
            t2.Wait();
            Console.WriteLine(unitedcell[0] + "  "  +unitedcell[1] + " "  + unitedcell[2]);
        }
    }
}