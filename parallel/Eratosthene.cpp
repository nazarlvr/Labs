#include <bits/stdc++.h>
#include <omp.h>
#include <sys/time.h>
using namespace std;
const int n = 1000000;
bool a[n];
ofstream f;
void check(int q)
    {
        auto qq = omp_get_thread_num();
        f << qq << " start with " << q << '\n';
        #pragma omp parallel for
        for (int i = 2 * q; i < n; i += q)
        {
            a[i] = 0;
        }

        f << qq << " end with " << q << '\n';
    }

    struct timeval tstart, tstop;



    int main() {
        gettimeofday(&tstart, NULL);
        f.open("log.txt");
        omp_set_num_threads(10);
        for (int i = 0; i < n; ++i)
            a[i] = 1;

        a[0] = 0;
        a[1] = 0;

        #pragma omp parallel for
        for (int i = 2; i < n; ++i)
        {
            if (i * i < n && a[i])
                check(i);
        }
        cout << endl << "Prime numbers up to " <<n<< ": " << endl;
        for (int i = 0; i < n; ++i)
        {
            if (a[i])
                f << i << " ";
        }
        f << endl;
        gettimeofday(&tstop, NULL);
        printf("time %dmcs\n", tstop.tv_sec*1000000LL + tstop.tv_usec - tstart.tv_sec*1000000LL - tstart.tv_usec);
        f.close();
    }
