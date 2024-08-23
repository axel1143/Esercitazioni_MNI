#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


void leggi_vettore(double *b,int n);
void stampa_vettore(double *b,int n);

int main (int argc, char *argv[]){

    double *vett,*local_vett,*vett1;
    int work[2];
    int dim,local_dim;
    int nproc,me;
       
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    
    if (me==0){
        printf("\n Dimensione del vettore=");
        fflush(stdout);
        scanf("%d",&dim);
        
        local_dim=dim/nproc;
        printf("\n Dimensione locale=%d\n\n",local_dim);
        fflush(stdout);
    
        work[0]=dim;
        work[1]=local_dim;
    }

    MPI_Bcast(&work[0],2,MPI_INT,0,MPI_COMM_WORLD);

    dim=work[0];
    local_dim=work[1];

    /**********************************************/
    /*******************ALLOCAZIONI ***************/
    
    vett=(double *)calloc(dim,sizeof(double));
    vett1=(double *)calloc(dim,sizeof(double));
    local_vett=(double *)calloc(local_dim,sizeof(double));
   
    
    /*********************************************/
    /*********************************************/
    
    if (me==0){
        printf("\n Inserisci le entrate del vettore vett:\n");
        fflush(stdout);
        leggi_vettore(vett,dim);
    }

    
    MPI_Scatter(&vett[0],local_dim,MPI_DOUBLE,&local_vett[0],local_dim,MPI_DOUBLE,0,MPI_COMM_WORLD);

    printf("\n Vettore local_vett sul processo %d",me);
    fflush(stdout);
    stampa_vettore(local_vett,local_dim);


    MPI_Gather(&local_vett[0],local_dim,MPI_DOUBLE,&vett1[0],local_dim,MPI_DOUBLE,0,MPI_COMM_WORLD);

    
    printf("\n Vettore vett1 su processo %d",me);
    fflush(stdout);
    stampa_vettore(vett1,dim);
        
    
    MPI_Finalize();


}


void leggi_vettore(double *b,int n){

    int i;
   
    for(i=0;i<n;i++){
        scanf("%lf",&b[i]);
    }    
    
}

void stampa_vettore(double *b,int n){
    
    int i;
    
    for(i=0;i<n;i++){
             printf("\n%25.17lf",b[i]);
             fflush(stdout);
             
    }

}  
