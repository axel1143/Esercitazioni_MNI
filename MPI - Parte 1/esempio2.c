#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    double a[2] = {0, 0}, b[2] = {0, 0};
    MPI_Init(&argc, &argv);

    MPI_Status status;
  
    // World size
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Proc Rank
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    // Proc name
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if(proc_rank == 0){
        printf("Io sono il proc n.%d\n", proc_rank);
        a[0] = 3.0 , a[1] =  5.0;
        printf("Contenuto a in partenza: %1f, %1f \n", a[0], a[1]);
        MPI_Send(&a[0], 2, MPI_DOUBLE, 1, 10, MPI_COMM_WORLD); 
    }

    else if (proc_rank == 1){
        MPI_Recv(&b[0], 2, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD, &status);
        printf("Io sono il proc n.%d\n", proc_rank);
        printf("Contenuto a: %1f, %1f \n", a[0], a[1]);
        printf("Contenuto b ricevuto: %1f, %1f \n", b[0], b[1]);
    }
   
    MPI_Finalize();
    return 0;
}