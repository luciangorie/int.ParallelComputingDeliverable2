#include <iostream>
#include "timecheck.h"  //personal library to check time
#include "matrice.h"
#include <cstring>  //personal library to allocate matrixes(matrice.h)
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{

    MPI_Init(&argc,&argv);
    
    Timer* tt=new Timer();
    Matrice m;
    m.createM();

    int rank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
    
    if(rank==0)
    {
    
    Matrice saved1;
    saved1.copyM(m);
    (*tt).startTimer();
    //m.stampaMatrice();
    
    
    
} 

    const int max_stop= m.size/3; //defining max stop for process
    
    //all rank launch 
    
    m.matTransposeBlock9(max_stop,rank);

    
    
    
































if(rank==0)
{

    (*tt).stopTimer();
    

    
    cout<<"\n";
    cout<<"Time 9 blocks with NO passing back messages:"<<(*tt).getElapsedTimeMicroseconds();
    
    
  
 
    
     
 }   
 
 
    

    
    
    
    
    // Finale
    MPI_Finalize();

    return 0;

}