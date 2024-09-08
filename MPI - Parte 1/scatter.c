#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void leggi_vettore(double *v, int n);
void stampa_vettore(double *v, int n);
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    MPI_Status status;

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int world_size, proc_rank, name_len;
    int dim, local_dim=0;
    double *vettore, *local_vett;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Get_processor_name(processor_name, &name_len);

    if(proc_rank == 0){
        
        printf("\n Inserisci la dimensione del vettore:\n");
        fflush(stdout);
        scanf("%d", &dim);

        vettore = (double*) calloc(dim, sizeof(double));
        printf("\n Inserisci il vettore: \n");
        fflush(stdout);
        leggi_vettore(vettore, dim);

        local_dim = dim/world_size;
        printf("\n Dimensione locale = %d\n", local_dim);
        fflush(stdout);
    }
    MPI_Bcast(&local_dim, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("\n Proc_rank = %d Local dim=%d\n",proc_rank, local_dim);
   
    local_vett = (double*) calloc(local_dim, sizeof(double));

    MPI_Scatter(&vettore[0], local_dim, MPI_DOUBLE, &local_vett[0], local_dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("\n Vettore local_vett sul processo %d: ",proc_rank);
    stampa_vettore(local_vett,local_dim);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}

void leggi_vettore(double *v, int n){
    int i;
    for (i = 0; i < n; i++){
        scanf("%lf", &v[i]);
    }
}

void stampa_vettore(double *v, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("\n%25.17lf", v[i]);
        fflush(stdout);
    }
}