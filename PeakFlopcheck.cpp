
#include<iostream>

using namespace std;

int main()
{
    int a;
    int time_micro;
    char s;
    cout<<"Write N size: ";
    cin>>a;
    cout<<"Write time in microseconds: ";
    cin>>time_micro;
    cout<<"Is it an MPI transposition?";
    cin>>s;
    
    int d=a/2;
    d--;
    a*=d;
    a*=3;
    
    if(s=='y'||s=='s')
    {
        d++;
        d*=2;
        d*=d;
        a+=d*2;
        //fixing case of matrix copy in MPI implementation, so more operations for the program 
        cout<<"if";
    }
    
    float z=(float)time_micro;
    float e=(float)a;
    
    cout<<"\n";
    cout<<"Effective peak performance: ";
    cout<<(e/z)/1000<<" GFLOPs / sec";
    
    
    
    
    
    return 0;
}
