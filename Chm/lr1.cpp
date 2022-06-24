#include <bits/stdc++.h>
#define probel "\n----------------------------------------------------------------------------\n"
#define e1 1e-4 //точність
#define kr 0.1 //коефіцієнт релаксації
using namespace std;

double f (double x)
{
    return  x * x + 4 * sin(x);
}

int d(double fi, double x0, double q) // функція підрахунку апріорної оцінки для методу простої ітерації
{
    return int((log(abs(fi - x0) / ((1 - q) * e1)))/ (log(1 / q))) + 1;
}

double fi (double x)
{
    return kr * f(x) + x;
}

double fi1 (double x)
{
    return x + 0.01 * pow(x, 4) * f(x);
}

pair<double, int> SimpleIterationMethod(double x0, double e)
        {
            int ko = 0;
            if (f(x0) == 0)
            {
                return make_pair(x0, 0);
            }
            double x1 = fi1(x0);
            while (abs(x1 - x0) >= e)
            {
                ko++;
                x0 = x1;
                x1 = fi1(x0);
            }
            return make_pair(x1, ko);
        }

pair<double, int> RelaxationMethod(double x0, double e)
        {
            int ko = 0;
            if (f(x0) == 0)
            {
                return make_pair(x0, 0);
            }
            double x1 = fi(x0);
            while (abs(x1 - x0) >= e)
            {
                ko++;
                x0 = x1;
                x1 = fi(x0);
            }
            return make_pair(x1, ko);
        }

int main()
{
    pair <double, int> p1 = SimpleIterationMethod (-1.75, e1);
    pair <double, int> p2 = RelaxationMethod (-7.5, e1);
    int aprior1 = d(-1.83192, -1.75, 0.792113);
    int aprior2 = d(-2.2502, -7.5, 0.361346);
    cout << "Simple Iteration Method: " << p1.first << '\n' << "CounterAprior: " << aprior1 << '\n' << "CounterPostPrior: " << p1.second << probel;
    cout << "Relaxation Method: " << p2.first << '\n' << "CounterAprior: " << aprior2 << '\n' <<  "CounterPostPrior: " << p2.second << probel;
}
