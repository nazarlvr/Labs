#include <bits/stdc++.h>
using namespace std;

const int N = 4;
double F[N + 1];
double Fderivative[N + 1][N + 1];
double X[N + 1];
double Xnext[N + 1];
double B[N + 1];

//метод релаксації
double alfa = 0.00001;
double Phi[N + 1];
double eps = 0.0001;

void XvectorInit()
{
    for (int i = 1; i <= N; i++)
        X[i] = i+0.3;
}
void FInitTest1()
{
    F[1] = X[1] * X[1] / (X[2] * X[2]) - cos(X[2]) - 2;
    F[2] = X[1] * X[1] + X[2] * X[2] - 6;

    /*F[1] = X[1] + X[2] - 3;
    F[2] = X[1] + 3 * X[2] - 7;*/
}

void FderivativeInitTest1()
{
    Fderivative[1][1] = 2 * X[1] / (X[2] * X[2]);
    Fderivative[1][2] = -2 * X[1] * X[1] / (X[2] * X[2] * X[2]) + sin(X[2]);
    Fderivative[2][1] = 2 * X[1];
    Fderivative[2][2] = 2 * X[2];
}

void FInitTest2()
{
    for (int i = 1; i <= N; i++)
    {
        F[i] = 0;
        for (int j = 1; j <= N; j++)
        {
            if (i == j)
                F[i] += (X[j] * X[j] * X[j] - j * j * j);
            else F[i] += (X[j] * X[j] - j * j);
        }
    }
}

void FderivativeInitTest2()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (i == j)
                Fderivative[i][j] = 3 * X[j] * X[j];
            else Fderivative[i][j] = 2 * X[j];
        }
    }
}

void BvectorInit()
{
    for (int i = 1; i <= N; i++)
    {
        B[i] = 0;
        for (int j = 1; j <= N; j++)
            B[i] += Fderivative[i][j] * X[j];

        B[i] = B[i] - F[i];
    }
}

void SLARsolutionForNewtonMethod()
{
    double L_Matrix[N + 1][N + 1];
    double U_Matrix[N + 1][N + 1];

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            U_Matrix[i][j] = 0;
            if (i == j) L_Matrix[i][i] = 1;
            else L_Matrix[i][j] = 0;
        }
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
        {
            if (i <= j)
            {
                double Sum = 0;
                for (int k = 1; k <= i - 1; k++)
                    Sum += L_Matrix[i][k] * U_Matrix[k][j];

                U_Matrix[i][j] = Fderivative[i][j] - Sum;

            }

            if (i > j)
            {
                double Sum = 0;
                for (int k = 1; k <= j - 1; k++)
                    Sum += L_Matrix[i][k] * U_Matrix[k][j];

                L_Matrix[i][j] = (Fderivative[i][j] - Sum) / U_Matrix[j][j];
            }
        }

    double y[N + 1];
    y[1] = B[1] / L_Matrix[1][1];
    for (int i = 2; i <= N; i++)
    {
        double subtrahend = 0;
        for (int j = 1; j <= i - 1; j++)
            subtrahend += L_Matrix[i][j] * y[j];

        y[i] = (B[i] - subtrahend) / L_Matrix[i][i];
    }

    Xnext[N] = y[N] / U_Matrix[N][N];
    for (int i = N - 1; i >= 1; i--)
    {
        double subtrahend = 0;
        for (int j = N; j > i; j--)
            subtrahend += U_Matrix[i][j] * Xnext[j];

        Xnext[i] = (y[i] - subtrahend) / U_Matrix[i][i];
    }
}


void NewtonMethodTest1()
{
    XvectorInit();
    FInitTest1();
    FderivativeInitTest1();
    BvectorInit();
    SLARsolutionForNewtonMethod();

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest1();
        FderivativeInitTest1();
        BvectorInit();

        SLARsolutionForNewtonMethod();

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

void NewtonMethodTest2()
{
    XvectorInit();
    FInitTest2();
    FderivativeInitTest2();
    BvectorInit();
    SLARsolutionForNewtonMethod();

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest2();
        FderivativeInitTest2();
        BvectorInit();

        SLARsolutionForNewtonMethod();

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

void PhiInit()
{
    for(int i = 1; i <= N; i++)
    {
        Phi[i] = X[i] + alfa * F[i];
    }
}

void RelaxationMethodTest1()
{
    XvectorInit();
    FInitTest1();
    PhiInit();

    for (int i = 1; i <= N; i++)
        Xnext[i] = Phi[i];

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest1();
        PhiInit();

        for (int i = 1; i <= N; i++)
            Xnext[i] = Phi[i];

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

void RelaxationMethodTest2()
{
    XvectorInit();
    FInitTest2();
    PhiInit();

    for (int i = 1; i <= N; i++)
        Xnext[i] = Phi[i];

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest2();
        PhiInit();

        for (int i = 1; i <= N; i++)
            Xnext[i] = Phi[i];

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

void PhiInitforSimpleIterationTest2()
{
    for (int i = 1; i <= N; i++)
    {
        Phi[i] = pow(-1 * F[i] + X[i] * X[i] * X[i], 1.0 / 3);
    }
}

void SimpleItaerationMethodTest2()
{
    XvectorInit();
    FInitTest2();
    PhiInitforSimpleIterationTest2();

    for (int i = 1; i <= N; i++)
        Xnext[i] = Phi[i];

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest2();
        PhiInitforSimpleIterationTest2();

        for (int i = 1; i <= N; i++)
            Xnext[i] = Phi[i];

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

void ModifiedNewtonMethodTest1()
{
    XvectorInit();
    FInitTest1();
    FderivativeInitTest1();
    BvectorInit();
    SLARsolutionForNewtonMethod();

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest1();
        BvectorInit();

        SLARsolutionForNewtonMethod();

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

void ModifiedNewtonMethodTest2()
{
    XvectorInit();
    FInitTest2();
    FderivativeInitTest2();
    BvectorInit();
    SLARsolutionForNewtonMethod();

    double delta = abs(Xnext[1] - X[1]);
    for (int h = 2; h <= N; h++)
        if (abs(X[h] - Xnext[h]) > delta)
            delta = abs(X[h] - Xnext[h]);

    while (delta > eps)
    {
        for (int h = 1; h <= N; h++)
            X[h] = Xnext[h];

        FInitTest2();
        BvectorInit();

        SLARsolutionForNewtonMethod();

        delta = abs(Xnext[1] - X[1]);
        for (int h = 2; h <= N; h++)
            if (abs(X[h] - Xnext[h]) > delta)
                delta = abs(X[h] - Xnext[h]);
    }
}

int main()
{
    NewtonMethodTest2();
    for (int i = 1; i <= N; i++)
        cout << Xnext[i] << " ";
    cout << endl;                       // нев'язка
    for (int i = 1; i <= N; i++)
        cout << F[i] << " ";

    cout << endl << endl;

    RelaxationMethodTest2();
    for (int i = 1; i <= N; i++)
        cout << Xnext[i] << " ";
    cout << endl;                       // нев'язка
    for (int i = 1; i <= N; i++)
        cout << F[i] << " ";

    cout << endl << endl;

    ModifiedNewtonMethodTest2();
    for (int i = 1; i <= N; i++)
        cout << Xnext[i] << " ";
    cout << endl;                       // нев'язка
    for (int i = 1; i <= N; i++)
        cout << F[i] << " ";

    cout << endl << endl;

    SimpleItaerationMethodTest2();
    for (int i = 1; i <= N; i++)
        cout << Xnext[i] << " ";
    cout << endl;                       // нев'язка
    for (int i = 1; i <= N; i++)
        cout << F[i] << " ";
}
