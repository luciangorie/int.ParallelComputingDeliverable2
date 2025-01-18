#include <iostream>
#include "timecheck.h"  //personal library to check time
#include "matrice.h"
#include <cstring>  
#include <mpi.h>
using namespace std;


void sendSubMatrix(Matrice& matrix, int startX, int startY, int subSize) {

    float* buffer = new float[subSize * subSize];
    int k=0;

    
    for (int i = startX; i < startX+subSize; i++) {
        for(int j=startY; j< startY+subSize;++j)
        {
          buffer[k++]=matrix.m[i][j];
        }
    }

    
    MPI_Send(buffer, subSize * subSize, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);

    
    delete[] buffer;
}

void recvSubMatrix(Matrice& matrix, int startX, int startY, int subSize, int sourceRank) {
    
    float* buffer = new float[subSize * subSize];
    int k=0;
    
    MPI_Recv(buffer, subSize * subSize, MPI_FLOAT, sourceRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    
    for (int i = startX; i < startX+subSize; i++) {
        for(int j=startY; j< startY+subSize;++j)
        {
          matrix.m[i][j]=buffer[k++];
        }
    }

    
    
    delete[] buffer;
}







int main(int argc, char *argv[])
{
Timer* tt=new Timer();
    MPI_Init(&argc, &argv);
    
    Matrice m;
    m.createM();
    
    

    int rank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
    
    if(rank==0)
    {
    
    Matrice saved1;
    saved1.copyM(m);
    
    //m.stampaMatrice();
    (*tt).startTimer();
    
    
} 

    const int max_stop= m.size/2; //defining max stop for process
    
    //all rank launch 
    
    m.matTransposeBlock4(max_stop,rank);  //in this way each rank transposes its part
    
    int startx=0;
    int starty=0;
    
    if(rank==1||rank==2)startx=max_stop;
    
    if(rank==1||rank==3)starty=max_stop;
  
  
    
    
    
    
    if(rank!=0)
    {
    sendSubMatrix(m,startx,starty,max_stop);
    }
    else
    {
    
      int qq=max_stop;
       
       recvSubMatrix(m,qq,0,max_stop,3);
       recvSubMatrix(m,qq,max_stop,max_stop,1);
       recvSubMatrix(m,0,max_stop,max_stop,2);
       
       
       (*tt).stopTimer();
       //m.stampaMatrice();
       //if(saved1.checkTransposeOf(m))cout<<"Correctly Transposed!";
       cout<<"Time taken for Block (4) transposition = "<<(*tt).getElapsedTimeMicroseconds();
       
       
    
    }
    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Finalize( );
    
    
    
    

    return 0;

}