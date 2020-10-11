#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct point
{
    int x;
    int y;
}point;

int main()
{
    point p,q;
    int a,b,d,mod,n;
    cout<<"Enter a&b in y^2=x^3+a.x+b and modulo:";
    cin>>a>>b>>mod;
    cout<<"Enter n:";
    cin>>n;
    int i,j;
    cout<<"points on curve are:\n";
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(((j*j)%mod) == ((i*i*i)+(a*i)+b)%mod)
            {
                cout<<"("<<i<<","<<j<<")\n";
            }
        }
    }
    cout<<"Select a point on the curve:";
    cin>>p.x>>p.y;
    while(1)
    {
        d=rand()%n;
        if(d!=0)
            break;
    }
    q.x=p.x*d; q.y=p.y*d;
    cout<<"private key:"<<d<<endl;
    cout<<"public key:"<<"("<<q.x<<","<<q.y<<")\n";
}