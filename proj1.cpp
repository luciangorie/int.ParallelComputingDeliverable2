#include <iostream>
#include "timecheck.h"  //personal library to check time
#include "matrice.h"
#include <cstring>  //personal library to allocate matrixes(matrice.h)
using namespace std;

int main(int argc, char* argv[])
{

    
  
    

    bool path=false;
    
    
    if (argc > 1 && strcmp(argv[1], "true") == 0) {
        path = true;
    }
    
    if (argc > 1 && strcmp(argv[1], "false") == 0) {
        path = false;
    }
    
    

    
    
    

    
    
    if(!path){
    
    Matrice t;
    t.createMsymmetric(1.1);
    
    Matrice m1,m2,m3,m4,m5,m6;
    m1.createM();
    m2.createM();
    m3.createM();
    m4.createM();
    m5.createM();
    m6.createM();
    
    
    Matrice saved1,saved2,saved3,saved4,saved5,saved6;
    saved1.createM();
    saved2.createM();
    saved3.createM();
    saved4.createM();
    saved5.createM();
    saved6.createM();
    saved1.copyM(m1);
    saved2.copyM(m1);
    saved3.copyM(m3);
    saved4.copyM(m4);
    saved5.copyM(m5);
    saved6.copyM(m6);
    
    
    Timer* tt=new Timer();
    (*tt).startTimer();
    bool safety=t.checkSym();
    (*tt).stopTimer();
    cout<<"Checking Symmetry :"<< (*tt).getElapsedTimeMicroseconds()<<"\n";
    
    
    
    
    
    m1.matTranspose();
    
    
    cout<<"\n";

    
     //safety= m1.checkTransposeOf(saved1);
  
  if(safety)
  {cout<<"Correctly transposed n.1";
   cout<<"\n";
   (*tt).startTimer();
    saved1.copyM(m1); 
    (*tt).stopTimer();
    cout<<"Time of copy  (full serial) = "<< (*tt).getElapsedTimeMicroseconds();
    //cout<<"\n"<<"which is :    "<<(*tt).getElapsedTimeMicroseconds()/10000<<" per data";
    
    }  //copying the calculated matrix in the new matrix T, counting also time taken for that this time
    
    
    
    
    }
   
   
    if(path) 
    {
    
    Matrice t;
    t.createMsymmetric(1.1);
    
    Matrice m1,m2,m3,m4,m5,m6;
    m1.createM();
    m2.createM();
    m3.createM();
    m4.createM();
    m5.createM();
    m6.createM();
    
    
    Matrice saved1,saved2,saved3,saved4,saved5,saved6;
    saved1.createM();
    saved2.createM();
    saved3.createM();
    saved4.createM();
    saved5.createM();
    saved6.createM();
    saved1.copyM(m1);
    saved2.copyM(m1);
    saved3.copyM(m3);
    saved4.copyM(m4);
    saved5.copyM(m5);
    saved6.copyM(m6);
    
    Timer* tp=new Timer();
    (*tp).startTimer();
    bool safety=t.checkSymImp();
    (*tp).stopTimer();
    cout<<"Checking Symmetry with implicit parallelism :"<<(*tp).getElapsedTimeMicroseconds()<<"\n";
    
    
    (*tp).startTimer();
     m1.matTransposeImp();
     

    safety= m1.checkTransposeOf(saved1);
  
    if(safety)
    {
    cout<<"n.1 Correctly Transposed";
   
    cout<<"\n";
    
    saved1.copyM(m1); //copying the calculated matrix in the new matrix T
    (*tp).stopTimer();
    cout<<"Time of transposition  (implicitly parallelized) = "<< (*tp).getElapsedTimeMicroseconds();
    cout<<"\n";
    }
    
    
   
    
    }
    
   


    return 0;

}