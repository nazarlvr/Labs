#include <bits/stdc++.h>
#define e 0.00001
const int n = 4;
using namespace std;
double A[n][n], B[n], x[n];

void stepmetod ()
{
    double x1[n], norma = 0, sum;
    do
    {
        sum = 0;
        for (int i = 0; i < n; ++i)
        {
            x1[i] = 0;
            for (int j = 0; j < n; ++j)
            {
                x1[i] += A[i][j] * x[j];
            }
            sum += x1[i];
        }

        norma = 0;

        for (int i = 0; i < n; i++) x1[i] /= 1. * sum;

        for (int i = 0; i < n; ++i)
        {
            if (norma < abs(x1[i] - x[i])) norma = abs(x1[i] - x[i]);
            x[i] = x1[i];
        }
    }
    while (norma > e);
}

int main()
{
cout << "Enter Transition or Probability Matrix(connected only) " << endl;
for (int i = 0; i < n; ++i) x[i] = 1. / n;
for (int i = 0; i < n; ++i)
{
    for (int j = 0; j < n; ++j)
        {
            cin >> A[i][j];
            B[j] += A[i][j];
        }
}
cout << "Connection Matrix A: " << endl;
for (int i = 0; i < n; ++i)
{
    for (int j = 0; j < n; ++j)
        {
            A[i][j] /= 1. * B[j];
            cout << A[i][j] << ' ';
        }
        cout << endl;
}
stepmetod();
cout << "Result Vector: " << endl << '(';
for (int i = 0; i < n - 1; ++i) cout << x[i] << ", "; cout << x[n-1];
cout << ')'<<endl;
}
