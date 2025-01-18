#include <iostream>
#include "timecheck.h"  //personal library to check time
#include "matrice.h"
#include <cstring>  //personal library to allocate matrixes(matrice.h)
#include <mpi.h>
using namespace std;

int main()
{
    Timer* tt=new Timer();
    MPI_Init(NULL,NULL);
    int s;
    Matrice m1;
    s=m1.size;
     int rank,nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    
   
    
    float send_queue[s];
    float buffer[s];
    float buff2[s];
    
    if(rank==0)
    {
    int ce=0;
    int q=0;
    
    
    m1.createM();
    //m1.stampaMatrice();
    
    (*tt).startTimer();
    
    
     while(q<s)
     { ce=0;
    while(ce<s)
    {
    send_queue[ce]=m1.m[q][ce];
    ++ce;
    } 
    if(q==0)
    {
      for(int t=0;t<s;++t)
      {
        buffer[t]=send_queue[t];
      }
    
    
    }
    else {
    
     MPI_Send(
    send_queue,          // Puntatore ai dati da inviare
    s,          // Numero di elementi nel buffer
    MPI_FLOAT, // Tipo di dati (es. MPI_INT, MPI_DOUBLE)
    q,           // Rank del processo destinatario
    0,            // Etichetta del messaggio
    MPI_COMM_WORLD       // Comunicatore (es. MPI_COMM_WORLD)
);
    
    
    
    
    
    
    
    }
    
    ++q; } 
    } 
    
    else 
    {
       MPI_Recv(buffer,s, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    //in this way each rank has a line
    
    MPI_Barrier(MPI_COMM_WORLD);
    //Putting Alltoall
    
    MPI_Alltoall ( buffer, 1, MPI_FLOAT , buff2 ,
    1, MPI_FLOAT , MPI_COMM_WORLD );
    
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    
    if(rank!=0)
    {
        MPI_Send(
    buff2,          // Puntatore ai dati da inviare
    s,          // Numero di elementi nel buffer
    MPI_FLOAT, // Tipo di dati (es. MPI_INT, MPI_DOUBLE)
    0,           // Rank del processo destinatario
    0,            // Etichetta del messaggio
    MPI_COMM_WORLD       // Comunicatore (es. MPI_COMM_WORLD)
);
    }
    else
    {
      
        float* xxx[s];  // Array di righe
        for (int i = 0; i < s; ++i) {
            xxx[i] = new float[s];  // Allocazione di una riga per ogni indice
        }

        
        for (int r = 1; r < s; ++r) {
            MPI_Recv(xxx[r], s, MPI_FLOAT, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        
        Matrice T;
        T.createM();
        
        int ce=0;
        int q=0;
        
        while(q<1)
        {
          ce=0;
          while(ce<s)
          {
            T.m[q][ce]=buff2[ce];
            ++ce;
          }
        q++;
        
        }
        
        while(q<s)
        {
          ce=0;
          while(ce<s)
          {
            T.m[q][ce]=xxx[q][ce];//assign
            ++ce;
          }
          ++q;
        }
        
        (*tt).stopTimer();
        
        
        cout<<"\n";
        //T.stampaMatrice();
         if(T.checkTransposeOf(m1))
        {
          cout<<"\n"<<"Correctly Transposed"<<"\n";
        
        
        }
        
        cout<<(*tt).getElapsedTimeMicroseconds();
        
        
        
    
    }
    
    
    MPI_Finalize();
   
    
    
    
    
    
    
    


    


    
    
    
    
    
    
    
   
   
       


    return 0;

}