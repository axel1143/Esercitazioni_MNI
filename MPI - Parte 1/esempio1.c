#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    
    MPI_Init(&argc, &argv);
  
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);


    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if(proc_rank == 0){
        printf("Questo è il mio rank: %d, e questa è la size del mondo: %d\n", proc_rank, world_size);
    }
    else if (proc_rank == 1){
        printf("Questo è il proc2\n");
        printf("La size del mondo è: %d\n", world_size);
    }

    MPI_Finalize();
    return 0;

    
}