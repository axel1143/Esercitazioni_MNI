#include <mpi.h>
#include <stdio.h>
void leggi_vettore(double *v, int n);
void stampa_vettore(double *v, int n);
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    MPI_Status status;

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int world_size, proc_rank, name_len, left, right, temp;

    double vettore[6] = {0, 0, 0, 0, 0, 0};

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Get_processor_name(processor_name, &name_len);

    if(proc_rank == 0){
        printf("Inserisci le 6 entrate del vettore!\n");
        fflush(stdout);
        leggi_vettore(vettore, 6);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(&vettore[0], 6, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    printf("\nVettore sul processo %d:\n", proc_rank);
    fflush(stdout);
    stampa_vettore(vettore, 6);


    // problema di questo script: le stampe vengon eseguite un po' casualmente, quindi non si visualizzano bene

    
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