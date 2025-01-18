#ifndef __MATRICE__
#define __MATRICE__
#include "timecheck.h"
#include <iostream>
#include <cstdlib>  // for rand() e srand()
#include <ctime> 


using namespace std;

typedef struct Matrice
{
    static const int size=2000;
    float m[size][size];
    
    Matrice()
    {
        //cout<<"Matrix allocated successfully "<<size<<" x "<<size;
        cout<<"\n";
    }

    void createM()
    {
        srand(static_cast<unsigned int>(time(0)));
        int ce=0;
        int i=0;
        //cout<<"Allocating floats";

        while(i<size)
        {
            ce=0;
            while(ce<size)
            {
                int k=rand()%10000+100;
                m[i][ce]=float(float(k)/100.000);
                ++ce;
            }
            ++i;
        }
       
    }
    
    void createMsymmetric(float x)
    {
        int ce=0;
        int i=0;
        //cout<<"Allocating floats";

        while(i<size)
        {
            ce=0;
            while(ce<size)
            {
                m[i][ce]=x;   //a matrix with all the same number x is symmetric
                ++ce;
            }
            ++i;
        }
       
    }
    
    
    

    void stampaMatrice()
    {
        cout<<"\n";
        int i=0;
        int ce=0;
        while(i<size)
        {
            ce=0;
            while(ce<size)
            {
                cout<<m[i][ce]<<" ";
                ++ce;
            }

            cout<<"\n";


            ++i;
        }
    }

    void matTranspose()
    {
    
        //Timer* ty= new Timer();
        //(*ty).startTimer();
        
    
        for (int i = 0; i < size; i++)
        {
        
            
            for (int j = i+1; j < size; j++)
            {
                
                float c = m[i][j];
                m[i][j] = m[j][i];
                m[j][i] = c;                 
                
                
                
                
                
            }
        }
        
        //(*ty).stopTimer();
        
        //cout<<"Internal time: "<<(*ty).getElapsedTimeMilliseconds();
        
        
   

    }

    void matTransposeImp()
    {
    
       // Timer* ty= new Timer();
       // (*ty).startTimer();
    
        float c;
        float e;
        
         for (int i = 0; i < size; ++i)
        {
            for (int j = i+1; j < size; ++j)
            {
                // swapping simple in sequential code quite as before
                c = m[i][j];
                e = m[j][i];
                m[j][i] = c;
                m[i][j]= e;
            }
            //cout<<"get";
        }
        
       // (*ty).stopTimer();
        
      //  cout<<"Internal time: "<<(*ty).getElapsedTimeMilliseconds();
        
       // cout<<"end!"<<"\n";
    

    }
    
    void matTransposeOMP()
    {
        float c;
    
        #pragma omp parallel for private(c)
        for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            c = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = c;
          }
        }
    }
    
    

    
    bool checkSym()
    {
        for (int i = 0; i < size; ++i)
        {
            for (int ce = i+1; ce < size; ++ce)
            {
                        if (m[i][ce] != m[ce][i])   return false;  
                      
            
            }
        }
        return true; 
    }
    
    bool checkSymImp()
    {
    
      Timer* tb=new Timer();
      (*tb).startTimer();
      
        for (int i = 0; i < size; ++i)
        {
            for (int ce = i+1; ce < size; ++ce)
            {
                        if (m[i][ce] != m[ce][i]) return false;  
                      
            
            }
        }
        (*tb).stopTimer();
        cout<<"Timer internal: "<<(*tb).getElapsedTimeMicroseconds();
        cout<<"\n";
        return true; 
    }
    
    bool checkSymOMP()
    {
    bool symmetric=true;
      #pragma omp parallel for shared(symmetric) 
    for (int i = 0; i < size; ++i) {
        for (int ce = i; ce < size; ++ce) {
            if (m[i][ce] != m[ce][i]) {
                #pragma omp critical // avoiding race condition
                symmetric = false;
                // Interrupting loops
                #pragma omp cancel for
            }
        }
    }

    return symmetric;
    }
    
     bool checkTransposeOf(const Matrice& m2)
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (m[i][j] != m2.m[j][i]) 
                {
                    return false; 
                }
            }
        }
        return true; 
    }
    
    void copyM(const Matrice& m2)
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                m[i][j] = m2.m[i][j];  
            }
        }
    }
    

 void matTransposeBlock4(int block_size, int id)
    {
        int start=0;
        int stop=block_size;
        int shift=0;
        float c;
        if(id==1||id==2)
        {
          start=stop;
          stop=block_size*2; 
          
        }//MANAGMENT OF ROWS
        
        if(id==2||id==3)
        {
            shift=block_size;
            if(id==2)shift*=-1;
        }//MANAGEMENT OF COLUMNS
        
        if(id==0||id==1)
        {
        for (int i = start; i < stop; ++i)
        {
            for (int j = i+1; j < stop; ++j)
            {
                c=m[i][j];
                m[i][j]=m[j][i];
                m[j][i]=c;
            }
        }
        }
        else
        {
        int saved;
          for (int i = start; i < stop; ++i)
        {
        
        
            
            if(id==2)
            {saved=i+shift;
            for (int j = i+1; j < stop; ++j)
            {
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
                
            }
            }
            else
            {saved=i+shift;
              for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }
            
            }
        }
        }
        
    
        
        
        
        
        
        
        
        
        
        
    }
    
    void matTransposeBlock9(int block_size, int id)
    {
        int start=0;
        int stop=block_size;
        int shift=0;
        float c;
        
        if(id==5||id==1||id==8)
        {
          start=stop;
          stop=block_size*2;
          
        }
        else if(id==3||id==6||id==2)
        {
          start=stop*2;
          stop=start+block_size;
        }
        
        
        if(id<3)
        {
        for (int i = start; i < stop; ++i)
        {
            for (int j = i+1; j < stop; ++j)
            {
                c=m[i][j];
                m[i][j]=m[j][i];
                m[j][i]=c;
            }
        }}//CLASSICAL TRANSPOSE FOR MIDDLE BLOCKS!
        else if(id==3)
        {
          int shift=block_size*-2;
          int saved;
          for (int i = start; i < stop; ++i)
          {
             saved=i-start;
          for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[(i+j+shift)-saved][saved];
                m[(i+j+shift)-saved][saved]=c;
            }}
        
        
        }//BOTTOM LEFT CORNER
        else if(id==4)
        {
          int shift=block_size*2;
          int saved;
          
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        
        
        
        
        }//UPPER RIGHT CORNER!
        else if(id==7||id==8)
        {
        int shift=block_size;
          int saved;
          
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        
        
        
        }
        else
        {
        int shift=block_size*-1;
          int saved;
          for (int i = start; i < stop; ++i)
          {
             saved=i+shift;
          for (int j = i+1; j < stop; ++j)
            {
                //if(id==6)cout<<"\n"<<"debug:"<<i<<" "<<j+shift<<" "<<i+j+shift-saved<<" "<<saved;
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        
        
        
        
        }}
        
        bool checkSymMPI(int r)
        {
          int start=0;
          int stop=size/2;
          if(r==1)
          {
            start=stop;
            stop*=2;
          
          }
          if(r==0||r==1)
          {
            //check symmetric classic
            
            for (int i = 0; i < size; ++i)
            {
            for (int ce = i+1; ce < size; ++ce)
            {
                        if (m[i][ce] != m[ce][i])   return false;  
                      
            
            }
          } 
            
          
          
          
          
          }
          else
          {
            
            for (int i = size/2; i < size; ++i)
            {
            for (int ce = 1; ce < size/2; ++ce)
            {
                        if (m[i][ce] != m[ce][i])   return false;  
                      
            
            }
        
          }
          
        
        }
        
        return true;  
        
        
        
    }
    
    
    void matTransposeBlock16(int block_size, int id)
    {
        int start=0;
        int stop=block_size;
        int shift=0;
        float c;
        
        if(id==10||id==1||id==14||id==9)
        {
          start=stop;
          stop=block_size*2;
          
        }
        else if(id==11||id==6||id==2||id==15)
        {
          start=stop*2;
          stop=start+block_size;
        }
        else if(id==4||id==7||id==12||id==3)
        {
          start=stop*3;
          stop=start+block_size;
        }
        
        
        if(id<4)
        {
        for (int i = start; i < stop; ++i)
        {
            for (int j = i+1; j < stop; ++j)
            {
                c=m[i][j];
                m[i][j]=m[j][i];
                m[j][i]=c;
            }
        }}//CLASSICAL TRANSPOSE FOR MIDDLE BLOCKS!
        else if(id==4||id==5)
        {
        int saved;
        int shift=3*block_size;
        if(id==4)shift*-1;
        
            
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        }
        else if(id==6||id==7)
        {
        int saved;
        int shift=-2*block_size;
         
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        }
        else if(id==8||id==9)
        {
        int saved;
        int shift=2*block_size;
         
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        }
        else if(id==10||id==11||id==12)
        {
        int saved;
        int shift=-1*block_size;
         
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        }
        else if(id==13||id==14||id==15)
        {
        int saved;
        int shift=1*block_size;
         
          for (int i = start; i < stop; ++i)
          {
          saved=i+shift;
           for (int j = i+1; j < stop; ++j)
            {
                
                c=m[i][j+shift];
                m[i][j+shift]=m[j][saved];
                m[j][saved]=c;
            }}
        }
        
        
        
        
        
        
        
        }
    
    
    
    
    
    
    
    
    

    


}Matrice;

#endif


