#include <bits/stdc++.h>
using namespace std;

const int k = 4;
double X1[k + 1], F[k + 1], B[k + 1], Fstr[k + 1][k + 1], X[k + 1];

void Newton1prepare()
{
    for (int i = 1; i <= k; i++)
        X[i] = i + 0.25;

    F[1] = pow(X[1], 2) / pow(X[2], 2) - cos(X[2]) - 2;
    F[2] = pow(X[1], 2) + pow(X[2], 2) - 6;

    Fstr[1][1] = 2 * X[1] / pow(X[2], 2);
    Fstr[1][2] = -2 * pow(X[1], 2) / pow(X[2], 3) + sin(X[2]);
    Fstr[2][1] = 2 * X[1];
    Fstr[2][2] = 2 * X[2];

    for (int i = 1; i <= k; i++)
    {
        B[i] = 0;
        for (int j = 1; j <= k; j++)
            B[i] += Fstr[i][j] * X[j];

        B[i] -= F[i];
    }
}

void Newton2prepare()
{
    for (int i = 1; i <= k; i++)
        X[i] = i + 0.25;

    for (int i = 1; i <= k; i++)
    {
        F[i] = 0;
        for (int j = 1; j <= k; j++)
        {
            if (i == j) F[i] += pow(X[j], 3) - pow(j, 3));
            else F[i] += pow(X[j], 2) - pow(j, 2));
        }
    }

    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (i == j)
                Fstr[i][j] = 3 * pow(X[j], 2);
            else Fstr[i][j] = 2 * X[j];
        }
    }

    for (int i = 1; i <= k; i++)
    {
        B[i] = 0;
        for (int j = 1; j <= k; j++)
            B[i] += Fstr[i][j] * X[j];

        B[i] -= F[i];
    }

}

void SLAR()
{
    double L[k + 1][k + 1], U[k + 1][k + 1];

    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            U[i][j] = 0;
            if (i == j) L[i][i] = 1;
            else L[i][j] = 0;
        }
    }

    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
        {
            if (i <= j)
            {
                double sum = 0;
                for (int w = 1; w <= i - 1; w++)
                    sum += L[i][w] * U[w][j];

                U[i][j] = Fstr[i][j] - sum;

            }

            if (i > j)
            {
                double sum = 0;
                for (int w = 1; w <= j - 1; w++)
                    sum += L[i][w] * U[w][j];

                L[i][j] = (Fstr[i][j] - sum) / U[j][j];
            }
        }

    double y[k + 1];
    y[1] = B[1] / L[1][1];
    for (int i = 2; i <= k; i++)
    {
        double sum = 0;
        for (int j = 1; j <= i - 1; j++)
            sum += L[i][j] * y[j];

        y[i] = (B[i] - sum) / L[i][i];
    }

    X1[k] = y[k] / U[k][k];
    for (int i = k - 1; i >= 1; i--)
    {
        double sum = 0;
        for (int j = k; j > i; j--)
            sum += U[i][j] * X1[j];

        X1[i] = (y[i] - sum) / U[i][i];
    }
}
void Newton1()
{
    Newton1prepare();
    SLAR();

    double delta = abs(X1[1] - X[1]);
    for (int q = 2; q <= k; q++)
        if (abs(X[q] - X1[q]) > delta)
            delta = abs(X[q] - X1[q]);

    while (delta > 0.0001)
    {
        for (int q = 1; q <= k; q++)
            X[q] = X1[q];

        F[1] = pow(X[1], 2) / pow(X[2], 2) - cos(X[2]) - 2;
        F[2] = pow(X[1], 2) + pow(X[2], 2) - 6;

        Fstr[1][1] = 2 * X[1] / pow(X[2], 2);
        Fstr[1][2] = -2 * pow(X[1], 2) / pow(X[2], 3) + sin(X[2]);
        Fstr[2][1] = 2 * X[1];
        Fstr[2][2] = 2 * X[2];

        for (int i = 1; i <= N; i++)
            {
                B[i] = 0;
                for (int j = 1; j <= k; j++)
                    B[i] += Fstr[i][j] * X[j];

                B[i] -= F[i];
            }

        SLAR();

        delta = abs(X1[1] - X[1]);
        for (int q = 2; q <= k; q++)
            if (abs(X[q] - X1[q]) > delta)
                delta = abs(X[q] - X1[q]);
    }
}

void Newton2()
{
    Newton2prepare();
    SLAR();

    double delta = abs(X1[1] - X[1]);
    for (int q = 2; q <= k; q++)
        if (abs(X[q] - X1[q]) > delta)
            delta = abs(X[q] - X1[q]);

    while (delta > 0.0001)
    {
        for (int q = 1; q <= k; q++)
            X[q] = X1[q];

        for (int i = 1; i <= k; i++)
        {
            F[i] = 0;
            for (int j = 1; j <= k; j++)
            {
                if (i == j) F[i] += pow(X[j], 3) - pow(j, 3));
                else F[i] += pow(X[j], 2) - pow(j, 2));
            }
        }

        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                if (i == j)
                    Fstr[i][j] = 3 * pow(X[j], 2);
                else Fstr[i][j] = 2 * X[j];
            }
        }
         for (int i = 1; i <= N; i++)
            {
                B[i] = 0;
                for (int j = 1; j <= k; j++)
                    B[i] += Fstr[i][j] * X[j];

                B[i] -= F[i];
            }

        SLAR();

        delta = abs(X1[1] - X[1]);
        for (int q = 2; q <= k; q++)
            if (abs(X[q] - X1[q]) > delta)
                delta = abs(X[q] - X1[q]);
    }
}

int main()
{
    NewtonMethodTest2();
    for (int i = 1; i <= N; i++)
        cout << Xnext[i] << " ";
}

