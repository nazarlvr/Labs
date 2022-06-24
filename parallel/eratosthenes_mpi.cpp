#include <iostream>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>
using namespace std;
struct timeval tstart, tstop;

ofstream f;
int main(int argc, char** argv)
{
    f.open("log.txt");
    int rank, n_ranks;
    // First call MPI_Init
    MPI_Init(&argc, &argv);
    gettimeofday(&tstart, NULL);
    // Get my rank and the number of ranks
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&n_ranks);

    int n = 100000;
    int *p = NULL, *s = NULL, *d = NULL;
    int rank_n = n / n_ranks;

    if (rank == 0)
    {
        p = (int*) malloc(sizeof(int) * n);

        for (int i = 0; i < n; ++i)
        {
            p[i] = i;
        }

        p[1] = 0;
    }

    s = (int*) malloc(sizeof(int) * rank_n);
    d = (int*) malloc(sizeof(int));

    if (rank == 0)
    {
        for (int i = 0; i * i < n; ++i)
        {
            if (p[i] != 0)
            {
                *d = p[i];
                MPI_Bcast(d, 1, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(p, rank_n, MPI_INT, s, rank_n, MPI_INT, 0, MPI_COMM_WORLD);

                for (int i = 0; i < rank_n; ++i)
                    if (s[i] % (*d) == 0 && s[i] != (*d))
                        s[i] = 0;

                MPI_Gather(s, rank_n, MPI_INT, p, rank_n, MPI_INT, 0, MPI_COMM_WORLD);
            }
        }

        *d = -1;
        MPI_Bcast(d, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Bcast(d, 1, MPI_INT, 0, MPI_COMM_WORLD);

        while (*d != -1)
        {
            MPI_Scatter(p, rank_n, MPI_INT, s, rank_n, MPI_INT, 0, MPI_COMM_WORLD);


            for (int i = 0; i < rank_n; ++i)
                if (s[i] % (*d) == 0 && s[i] != (*d))
                    s[i] = 0;

            MPI_Gather(s, rank_n, MPI_INT, p, rank_n, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(d, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0)
    {
        for (int i = 0; i < n; ++i)
        {
            if (s[i])
                f << i << " ";
        }
    }

    // Call finalize at the end
    gettimeofday(&tstop, NULL);
    f << "time " << (tstop.tv_sec * 1000000LL + tstop.tv_usec - tstart.tv_sec * 1000000LL - tstart.tv_usec) << " ms";
    f << '\n';
    f.close();
    return MPI_Finalize();
}
