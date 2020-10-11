#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
int p=3,q=7;

double convert(string a)
{
    double b=0;
    for(int i=0;i<a.size();i++)
    {
        b=(b*10) + a[i] - 'a' + 1;
    }
    return b;
}

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
int main()
{
    double n,e=2,d=2,phi;
    string input;
    cout<<"Enter the plain text:";
    cin>>input;
    cout<<"The numbered input is:"<<convert(input)<<endl;
    phi=(p-1)*(q-1);

    //Finding public keys
    n=p*q;

    cout<<"n="<<n<<" phi="<<phi<<endl;
    
    while(e<phi)
    {
        if(__gcd((int)e,(int)phi)==1)
            break;
        else
            e++;
    }

    d=inver_modulo(e,phi);

    cout<<"e="<<e<<" d="<<d<<endl;
    double in=convert(input),c=pow(in,e);
    c=fmod(c,n);
    cout<<"Encrypted text:"<<c<<endl;

    double m=pow(c,d);
    m=fmod(m,n);
    cout<<"Decrypted text:"<<m<<endl;
}