#include <mpi.h>
#include <stdio.h>
#define ROOT 0
#define MSG_TAG 100

int main(int argc, char **argv)
{
	int tid,size;
	MPI_Status status;

	MPI_Init(&argc, &argv); //Musi być w każdym programie na początku

	printf("Checking!\n");
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &tid );
	printf("My id is %d from %d\n",tid, size);

	int msg[2];

	int count;

	if ( tid == ROOT)
	{
		count = 0;
		//for(int i =0;i<size-1;i++)
		//{
		MPI_Send( &count, 1, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD );
		printf(" Wyslalem %d do %d\n", count, 1 );
		MPI_Recv(&count, 1, MPI_INT, size-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("FNL ############");
		printf(" Otrzymalem %d od %d\n", count, status.MPI_SOURCE);
		printf("FNL ############");
		//}	
	}
	else
	{
		//msg[0] = tid;
		//msg[1] = size;
		MPI_Recv(&count, 1, MPI_INT, tid-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf(" Otrzymalem %d od %d\n", count, status.MPI_SOURCE);
		count++;
		if(tid+1<=size-1){
			MPI_Send( &count, 1, MPI_INT, tid+1, MSG_TAG, MPI_COMM_WORLD );
			printf(" Wyslalem %d do %d\n", count, tid+1);
		}
		else{
			MPI_Send( &count, 1, MPI_INT, ROOT, MSG_TAG, MPI_COMM_WORLD );
			printf(" Wyslalem %d do %d\n", count, 0);
		}
	}

	MPI_Finalize(); // Musi być w każdym programie na końcu
}
