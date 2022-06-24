using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace OSPhilosophersProblem
{
    class ForkState
    {
        public bool taken { get; set; } = false;
        public int ownerNumber { get; set; } = -1;
        public bool leftNeighborRequest { get; set; } = false;
        public bool rightNeighborRequest { get; set; } = false;
        public byte leftNeighborPriority { get; set; } = 0;
        public byte rightNeighborPriority { get; set; } = 0;
    }

    enum PhilosopherState
    {
        Hungry,
        Think,
        Eat
    }

    class Philosopher
    {
        public int Number { get; }
        public PhilosopherState state { get; private set; }

        public Philosopher(int num) => Number = num;
        public void Eat()
        {
            state = PhilosopherState.Eat;
            Console.WriteLine($"Philosopher {Number} is eating ");
            Random rnd = new Random();
            Thread.Sleep(rnd.Next(3000, 5000));
            state = PhilosopherState.Think;
        }

        public void Think()
        {
            state = PhilosopherState.Think;
            Console.WriteLine($"Philosopher {Number} is thinking ");
            Random rnd = new Random();
            Thread.Sleep(rnd.Next(4000, 6000));
            state = PhilosopherState.Hungry;
        }
    }

    class PhilosophersTask
    {
        ForkState[] forkStates = new ForkState[5];
        Philosopher[] philosophers = new Philosopher[5];

        public PhilosophersTask()
        {
            for (int i = 0; i < 5; i++)
            {
                forkStates[i] = new ForkState();
                philosophers[i] = new Philosopher(i);
            }
        }

        public void ProcessPhilosopher(int num)
        {
            var philosopher = philosophers[num];
            while (true)
            {
                if (philosopher.state == PhilosopherState.Think || philosopher.state == PhilosopherState.Eat)
                {
                    continue;
                }
                else
                {
                    if (num < 4)
                    {
                        if (forkStates[num].ownerNumber != num)
                            TakeRightFork(num);
                        if (forkStates[num].ownerNumber == num)
                            TakeLeftFork(num);
                    }
                    else
                    {
                        if (forkStates[0].ownerNumber != 4)
                            TakeLeftFork(4);
                        if (forkStates[0].ownerNumber == 4)
                            TakeRightFork(4);
                    }

                    if (forkStates[num].ownerNumber == num && forkStates[(num + 1) % 5].ownerNumber == num)
                    {
                        philosopher.Eat();
                        if (num < 4)
                        {
                            PutLeftFork(num);
                            PutRightFork(num);
                        }
                        else
                        {
                            PutRightFork(num);
                            PutLeftFork(num);
                        }
                        philosopher.Think();
                    }
                }
            }
        }

        public void TakeRightFork(int philosopherNum)
        {
            var fork = forkStates[philosopherNum];
            lock (fork)
            {
                if (fork.taken == false)
                {
                    if (fork.rightNeighborRequest == false)
                    {
                        fork.taken = true;
                        fork.ownerNumber = philosopherNum;
                    }
                    else
                    {
                        if (fork.leftNeighborPriority >= fork.rightNeighborPriority)
                        {
                            fork.taken = true;
                            fork.ownerNumber = philosopherNum;
                        }
                        else fork.leftNeighborRequest = true;
                    }
                }
                else fork.leftNeighborRequest = true;
            }
        }

        public void TakeLeftFork(int philosopherNum)
        {
            var fork = forkStates[(philosopherNum + 1) % 5];
            lock (fork)
            {
                if (fork.taken == false)
                {
                    if (fork.leftNeighborRequest == false)
                    {
                        fork.taken = true;
                        fork.ownerNumber = philosopherNum;
                    }
                    else
                    {
                        if (fork.rightNeighborPriority >= fork.leftNeighborPriority)
                        {
                            fork.taken = true;
                            fork.ownerNumber = philosopherNum;
                        }
                        else fork.rightNeighborRequest = true;
                    }
                }
                else fork.rightNeighborRequest = true;
            }
        }

        public void PutLeftFork(int philosopherNum)
        {
            var fork = forkStates[(philosopherNum + 1) % 5];
            lock (fork)
            {
                fork.taken = false;
                fork.ownerNumber = -1;
                fork.rightNeighborRequest = false;
                fork.rightNeighborPriority = 0;
                fork.leftNeighborPriority = 1;
            }
        }
        public void PutRightFork(int philosopherNum)
        {
            var fork = forkStates[philosopherNum];
            lock (fork)
            {
                fork.taken = false;
                fork.ownerNumber = -1;
                fork.leftNeighborRequest = false;
                fork.leftNeighborPriority = 0;
                fork.rightNeighborPriority = 1;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            PhilosophersTask philosophersTask = new PhilosophersTask();
            Parallel.For(0, 5, philosophersTask.ProcessPhilosopher);
        }
    }
}

