#include <bits/stdc++.h>

#define pr "\n\n\n"
const int r = 30;
const int rand_oper = 50;
const double e = 0.00001;
using namespace std;
double A[r][r], l[r][r], u[r][r], B[r], x[r], y[r];

ostream& operator << (ostream& out, double er[r])
{
    out << "Array with answer X:" << endl;
    for (int i = 0; i < r; ++i)
    {
        out <<  er[i] << ' ';
    }
    out << fixed << setprecision(3) << endl;
    return out;
}

void generate_lu()
{
for (int i = 0; i < r; ++i)
{
    u[i][i] = 1;
}

for (int i = 0; i < r; ++i)
{
    for (int j = 0; j < r; ++j)
    {
        if (i >= j)
            {
                l[i][j] = A[i][j];
                for (int k = 0; k < j; ++k)
                {
                    l[i][j] -= l[i][k] * u[k][j];
                }
            }
        else
        {
            u[i][j] = A[i][j];
            for (int k = 0; k < i; ++k)
            {
                u[i][j] -= l[i][k] * u[k][j];
            }
            u[i][j] /=  1. * l[i][i];
        }
    }
}
}


void metod_lu()
{
    generate_lu();
y[0] = 1. * B[0] / l[0][0];
//cout << "y[0]=" << y[0] << endl;
double sum = 0;
for (int i = 1; i < r; ++i)
{
    sum = 0;
    for (int j = 0; j < i; ++j)
    {
        sum += l[i][j] * y[j];
    }
    y[i] = (1. * (B[i] - sum)) / l[i][i];
    //cout <<"y[" << i << "]=" << y[i] << endl;
}
x[r - 1] = y[r - 1];
sum = 0;
for (int i = r - 2; i >= 0; i--)
{
    sum = 0;
    for (int j = r - 1; j > i; --j)
    {
        sum += u[i][j] * x[j];
    }
    x[i] = 1. * (y[i] - sum);
}
}

void generate_x_z()
{
    for (int i = 0; i < r; ++i)
    {
        x[i] = 0;
    }
}
void generate_x_j()
{
    for (int i = 0; i < r; ++i)
    {
        x[i] = 1. * B[i] / A[i][i];
    }
}

void generate_x1()
{
    for (int i = 0; i < r; ++i)
    {
        int sum = 0;
        for (int j = 0; j < r; ++j)
        {
            sum += A[i][j];
        }
        //cout << sum<<endl;
        B[i] = sum;
    }
}
void generate_hilberd_matrix()
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            A[i][j] =  1. / (i + j + 1);
        }
        B[i] = 1;
    }
}

bool umova_vyhodu(double q[r])
{
    double norma = 0;
	for (int i = 0; i < r; ++i)
		norma += (1. * x[i] - 1. * q[i]) * (1. * x[i] - 1. * q[i]);
	return (sqrt(norma) < e);
}

void metod_zeidelya()
{
    double Pocket[r];
    do
		{
		    //cout << x;
			for (int i = 0; i < r; i++) {Pocket[i] = x[i];}
			for (int i = 0; i < r; ++i)
			{
				double sum1 = 0;
				for (int j = 0; j < i ; j++)
					sum1 += (A[i][j] * x[j]);
				for (int j = i + 1; j < r; j++)
					sum1 += (A[i][j] * Pocket[j]);
				x[i] = (B[i] - sum1) / A[i][i];
			}
			for (int j = 0; j < r; ++j) cout << x[j] << ' ';
			cout << endl;
		} while (!umova_vyhodu(Pocket));
}

void coutmatrix(double q[r][r], int f, double w[r])
{
    cout << "Matrix A:" << endl;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            cout << fixed << setprecision(3) << q[i][j] << ' ';
        }
        cout << endl;
    }
    if (f){
    cout << "Matrix B:" << endl;
    for (int j = 0; j < r; ++j)
        {
            cout << fixed << setprecision(3) << w[j] << ' ';
        }
    cout << endl;
    }
}

void Generate_random_Matrix()
{
srand (/*time(0)*/8);
for (int i = 0; i < r; ++i)
{
    int sum = 0;
    for (int j = 0; j < r; ++j)
    {
        //int a = rand() % (rand_oper * 50);
        int b = 1 + rand() % rand_oper;

        //A[i][j] = 1.* a / b;
        A[i][j] = b;

        int z = rand() % 2;
        if (z) A[i][j] *= -1;
        sum += abs(A[i][j]);
    }
    sum -= abs(A[i][i]);
    int g = 1 + rand() % rand_oper;
    A[i][i] = sum + g;
    //int a = rand() % rand_oper;
    int b = 1 + rand() % rand_oper;
    //B[i] = 1.* a / b;
    B[i] = b;
    int z = rand() % 2;
    if (z) B[i] *= -1;
}
}
void metod_jacobi()
{
	double norma, Pocket[r];
	do {
		for (int i = 0; i < r; i++)
        {
			Pocket[i] = B[i];
            for (int j = 0; j < r; j++)
            {
				if (i != j) Pocket[i] -= A[i][j] * x[j];
			}
			Pocket[i] /= A[i][i];
		}
        norma = fabs(x[0] - Pocket[0]);
		for (int i = 0; i < r; i++)
		{
            norma = max(norma, fabs(x[i] - Pocket[i]));
			x[i] = Pocket[i];
		}
	} while (norma > e);
}

void fix_matrix()
{
    int sum;
    for (int i = 0; i < r; ++i)
    {
        sum = - A[i][i];
        for (int j = 0; j < r; ++j)
        {
            sum += A[i][j];
        }
        if (sum > A[i][i]) A[i][i] = 1. * sum + 15.1;
    }
    cout << "Matrix fixed" << endl;
}

void start()
{
generate_hilberd_matrix();
//generate_x1();
/*coutmatrix(A, 1, B);
metod_lu();
cout << "Metod LU(Hilbert): " << endl;
cout << x;
*/
Generate_random_Matrix();
generate_x1();
coutmatrix(A,1,B);
cout << pr;
cout << "Metod LU: " << endl;
metod_lu();
cout << x;
cout << pr;
generate_x_j();
cout << "Metod Jacobi: " << endl;
cout << "Start vector: " << endl;
cout << x;
cout << endl;
metod_jacobi();
cout << x;
cout << pr;
generate_x_z();
cout << "Metod Zeidelya: " << endl<< endl;
cout << "Start vector: " << endl ;
cout << x;
cout << endl;
metod_zeidelya();
cout << x;
}
int main()
{
start();
}
