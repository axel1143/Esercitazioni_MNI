#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    MPI_Status status;

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int world_size, proc_rank, name_len, left, right, temp;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Get_processor_name(processor_name, &name_len);

    left = (proc_rank-1+world_size)%world_size;
    // x  = (0 - 1 + 4)%4 = 0 resto 3  
    // x1 = (1 - 1 + 4)%4 = 1 resto 0
    // x2 = (2 - 1 + 4)%4 = 1 resto 1
    // 3 0 1 2

    right = (proc_rank+1)%world_size;
    // y = (0+1)%4 = 0 resto 1
    // y1 = (1+1)%4  = 0 resto 2
    // y2 = (2+1)%4 = 0 resto 3
    // 1 2 3 0

    MPI_Send(&proc_rank, 1, MPI_INT, right, 25, MPI_COMM_WORLD);
    MPI_Recv(&temp, 1, MPI_INT, left, 25, MPI_COMM_WORLD, &status);

    printf("Ciao sono il processo %d, ed ho ricevuto %d dal prcesso alla mia sinistra: %d\n", proc_rank, temp, left);
    
    MPI_Finalize();
    return 0;
}