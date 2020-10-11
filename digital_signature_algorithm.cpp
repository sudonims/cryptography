#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
int inver_modulo(int a,int mod)
{
    a%=mod;
    for(int i=1;i<mod;i++)
    {
        if((a*i) %mod==1)
        {
            return i;
        }
    }
}

int modulo(int a,int mod)
{
    if(a>0)
        return a%mod;
    else if(a<0)
        return mod+(a%mod);
    else 
        return 0;
}
int main()
{
    size_t p=47,q=23,h,g,x,y;
    cout<<"enter h:";
    cin>>h;
    g=pow(h,(p-1)/q);

    cout<<"Global keys:("<<p<<","<<q<<","<<g<<")\n";
    cout<<"Enter x:";
    cin>>x;
    y=fmod(pow(g,x),p);
    cout<<"Public Key:"<<y<<endl;


    size_t k,r,e=5;
    long long s;
    cout<<"Enter k:";
    cin>>k;
    r=fmod(fmod(pow(g,k),p),q);
    s=modulo(inver_modulo(k,q)*modulo(e,q),q) + modulo(x*r,q);

    cout<<"Signature:("<<r<<","<<s<<")\n";



    long long w=inver_modulo(s,q);
    size_t u1=fmod(e*w,q),u2=fmod(r*w,q);

    size_t v= fmod(fmod(pow(g,u1)*pow(y,u2),p),q);

    cout<<"Verified";
}