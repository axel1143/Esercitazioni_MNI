
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>

int main (int argc, char **argv)
{
	int rank, nproc; //	Necessarie MPI
	MPI_Status status;

	int num_elementi, resto, numero_loc, numero_gen, i, assegnati, tag;
	int *vettore_elementi, *vettore_loc;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);

	// PARTE 0 - INIZIALIZZAZIONE VETTORE ELEMENTI

	if(rank == 0){
		printf("Inserire il numero di elementi da sommare: \n");
		fflush(stdout);
		scanf("%d", &num_elementi);

		vettore_elementi = (int*) calloc(num_elementi, sizeof(int));
	}

	MPI_Bcast(&num_elementi, 1, MPI_INT, 0, MPI_COMM_WORLD);

	resto = num_elementi%nproc;
	numero_gen = num_elementi/nproc;

	if(rank < resto)
		numero_loc = numero_gen+1;
	else
		numero_loc = numero_gen;
	

	vettore_loc = (int*) calloc(numero_loc, sizeof(int));

	if(rank == 0)
	{
		//GENERAZIONE ELEMENTI CASUALI
		srand((unsigned int) time(0));

		for (i = 0; i< num_elementi; i++)
			*(vettore_elementi+i) = (int) rand()%5-2;

	// PARTE 1 -- DISTRIBUZIONE ELEMENTI A PROCESSORI

		//DISTRIBUZIONE A P0
		for (i = 0; i < numero_loc; i++)
			*(vettore_loc+i) = *(vettore_elementi+i);
		
		assegnati = numero_loc;


		//DISTRIBUZIONE A P SUCCESSIVI
		for (i = 1; i < nproc; i++)
		{
			tag=i;
			if(i < resto){
				MPI_Send(vettore_elementi+assegnati, numero_gen+1, MPI_INT, i, tag, MPI_COMM_WORLD);
				assegnati = assegnati + numero_gen+1;
			}
			else{
				MPI_Send(vettore_elementi+assegnati, numero_gen, MPI_INT, i, tag, MPI_COMM_WORLD);
				assegnati = assegnati + numero_gen;
			}
		}

		for(int j = 0; j < num_elementi; j++){
			printf("%d ", vettore_elementi[j]);
		}

		
		
	}
	else //SE NON SIAMO P0, RICEVIAMO
	{
		tag = rank;
		MPI_Recv(vettore_loc,numero_loc, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	// PARTE 2 -- CALCOLO SOMME PARZIALI
	printf("proc:%d\n", rank);
	for (int j = 0; j<numero_loc; j++){
		printf("%d ", *(vettore_loc+j));
	}

	MPI_Finalize();
}
