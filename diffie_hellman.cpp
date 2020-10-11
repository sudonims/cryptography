#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    size_t A,B,a,b,g,p,skey;
    cout<<"Enter prime number p and g:";
    cin>>p>>g;
    g=fmod(g,p);
    cout<<"Select a and b:";
    cin>>a>>b;
    A=(size_t)pow(g,a) %p;
    B=(size_t)pow(g,b) %p;
    cout<<"Exchanging A and B through insecure channel..\n";
    skey=(size_t)pow(A,b) %p;
    cout<<"skey by A:"<<(size_t)pow(A,b) %p<<" skey by B:"<<(size_t)pow(B,a) %p<<endl;
}