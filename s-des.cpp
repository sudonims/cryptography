//S-Des
#include<iostream>
#include<vector>
using namespace std;
#define pb push_back

//Initialized Vectors for making permutations
vector<int> ip={2,6,3,1,4,8,5,7};
vector<int> ep={4,1,2,3,2,3,4,1};
vector<int> ipi={4,1,3,5,7,2,8,6};
vector<int> p4i={2,4,3,1};
string key1="10100100",key2="01000001";
vector<vector<string>> s0={ {"01","00","11","10"},
                            {"11","10","01","00"},
                            {"00","10","01","11"},
                            {"11","01","11","10"} };

vector<vector<string>> s1={ {"00","01","10","11"},
                            {"10","00","01","11"},
                            {"11","00","01","00"},
                            {"10","01","00","11"} };

//Converts 2-bit binary to decimal
int bin_dec(string a)
{
    if(a=="00")
        return 0;
    else if(a=="01")
        return 1;
    else if(a=="10")
        return 2;
    else if(a=="11")
        return 3;
}

//XORs two binary strings
string x_or(string str,string str1)
{
    string a; int i;
    for(i=0;i<str.size();i++)
    {
        if(str[i]==str1[i])
        {
            a.pb('0');
        }
        else
        {
            a.pb('1');
        }
    }
    return a;
}

//Converts given string to its respective EP output
string con_ep(string str)
{
    string a;
    for(int i=0;i<8;i++)
    {
        a.pb(str[ep[i]+3]);
    }
    return a;
}

//Converts given string to IP/IP_inverse
string con_ip_i(string str,vector<int> a)
{
    string b;
    for(int i=0;i<a.size();i++)
    {
        b.pb(str[a[i]-1]);
    }
    return b;
}

//Round "function".This is where magic happens
string fg(string str,string key)
{
    string four_bit,p4,ep=con_ep(str),inter;
    cout<<"EP is:"<<ep<<endl;
    inter=x_or(ep,key);
    string a=inter.substr(0,1)+inter.substr(3,1),
           b=inter.substr(1,1)+inter.substr(2,1),
           c=inter.substr(4,1)+inter.substr(7,1),
           d=inter.substr(5,1)+inter.substr(6,1);

    string i_s0=s0[bin_dec(a)][bin_dec(b)],i_s1=s1[bin_dec(c)][bin_dec(d)];
    p4=i_s0+i_s1;
    p4=con_ip_i(p4,p4i);
    for(int i=0;i<4;i++)
    {
        four_bit.pb(str[i]);
    }
    cout<<"P4 is:\n"<<p4<<endl;
    string xord=x_or(p4,four_bit);
    return xord;
}

//Strips last 4 bits of the string
string last_four(string a)
{
    string b;
    for(int i=4;i<8;i++)
    {
        b.pb(a[i]);
    }
    return b;
}

int main()
{
    string input,intermediate,ep,inter;
    int i,j,k,l;
    cout<<"Enter plain text:\n";
    cin>>input;
    intermediate=con_ip_i(input,ip);
    cout<<"Initial Permutation is:"<<intermediate<<endl;

    intermediate=last_four(intermediate)+fg(intermediate,key1);
    cout<<"after fk1 and swap:"<<intermediate<<endl;

    intermediate=fg(intermediate,key2)+last_four(intermediate);
    cout<<"after fk2:"<<intermediate<<endl;
    intermediate=con_ip_i(intermediate,ipi);
    cout<<"\nThe ciphered string is:\n"<<intermediate<<endl;
}
