#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define ROOT 0
#define MSG_TAG 100
#define RAND_SIZE 1500000000

int main(int argc,char **argv)
{
    int size,tid;
    long double R = 1;

    long double x;
    long double y;

    MPI_Init(&argc, &argv); 

    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &tid );

    srand( tid );

    int res;
    //printf("ELO\n");
    if ( tid == 0 ) {
	MPI_Status status;
        int i;
        long double pi;
        long double total = 0;
	    // pewnie jakiś for tutaj
        for(i=0;i<size-1;i++){
	        MPI_Recv( &res, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            //printf("%d\n", res);
            total += res;
        }
        printf("%d\n", total);
        printf("%d\n", RAND_SIZE * (size -1));
        pi = 4.0*((long double)total / (long double)(RAND_SIZE * (size -1)));
        printf("Przybliżenie pi po zebraniu danych od %d procesów wynosi %llf\n", i, pi);
    } else {
        // int x = rand() % R;
        res = 0;
        for(int i=0;i<RAND_SIZE;i++){
            x = ((long double)rand()/(long double)(RAND_MAX)) * R;
            y = ((long double)rand()/(long double)(RAND_MAX)) * R;
            //x = rand()%R;
            //y = rand()%R;
            if(x*x + y*y <= R*R) res++;
        }
        //printf("%d\n", res);
        // pewnie jakiś for tutaj
	    MPI_Send( &res, 1, MPI_INT, ROOT, MSG_TAG, MPI_COMM_WORLD );
    }

    MPI_Finalize();
}
