#include <mpi.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSG_TAG 100
#define PROCSIZE 10

/* 4 literowe
aa5UYq6trT5u.
bahAZ9Hk7SCf6
ddoo3WocSpthU
jkmD2RlhoMyuA
zzm4NUIIb7VIk
kkv864igyJC9o

5 literowe
aaSPfLTmjh3fU

6 literowe
aaLTdQr7DyHuU 
*/

char *stro="aaLTdQr7DyHuU";


int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    MPI_Status status;
    int size,rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    char cmp[7]={0};

    char salt[3]={0};
    salt[0]=stro[0];
    salt[1]=stro[1];

    /* Ten fragment kodu nalezy _jakos_ zrównoleglić */
    /* pewnie będzie potrzebna jakaś pętla... */
    if(rank==0){
        int n =0;
        for(char i='a'; i<='z';i++){
            n++;
            cmp[0] = i;
            MPI_Send(cmp,7,MPI_INT, n ,MSG_TAG, MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(cmp, 7, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        for(char i = 'a'; i<='z';i++){
            cmp[1]=i;
            for(char j = 'a'; j<='z';j++){
                cmp[2]=j;
                for(char k = 'a'; k<='z';k++){
                    cmp[3]=k;
                    for(char l = 'a'; l<='z';l++){
                    cmp[4]=l;
                    for(char m = 'a'; m<='z';m++){
                    cmp[5]=m;
                    char * x=crypt(cmp, salt);

                    if ((strcmp(x,stro))==0)
                    {
                        /* w docelowej wersji przeslac odgadnięte hasło masterowi */
	                    printf("Udalo sie: %s %s %s\n", cmp, x, stro);

                        MPI_Abort(MPI_COMM_WORLD, 911);
                        MPI_Finalize();
	                    exit(0);
                    }
                }}}}}
    }
    /* Koniec fragmentu kodu */

    MPI_Finalize();
}
