#include<iostream>
#include<vector>
using namespace std;
#define pb push_back

vector<int> Parity_Drop={ 57,49,41,33,25,17,9,1,
                        58,50,42,34,26,18,10,2,
                        59,51,43,35,27,19,11,3,
                        60,52,44,36,63,55,47,39,
                        31,23,15,7,62,54,46,38,
                        30,22,14,6,61,53,45,37,
                        29,21,13,05,28,20,12,4 };

vector<int> Compr_D_Box={ 14, 17, 11, 24, 01, 05, 03, 28,
                        15, 06, 21, 10, 23, 19, 12, 04,
                        26, 8, 16, 07, 27, 20, 13, 02,
                        41, 52, 31 ,37, 47, 55, 30, 40,
                        51, 45, 33, 48, 44, 49, 39, 56,
                        34, 53, 46, 42, 50, 36, 29, 32 };

string comp_D(string a)
{
    string b;
    for(int i=0;i<Compr_D_Box.size();i++)
    {
        b.pb(a[Compr_D_Box[i]-1]);
    }
    return b;
}

string strip(string a,int b)
{
    string c;
    int i;
    if(b==1)
    {
        for(i=0;i<28;i++)
        {
            c.pb(a[i]);
        }
    }
    else if(b==2)
    {
        for(i=28;i<56;i++)
        {
            c.pb(a[i]);
        }
    }
    return c;
}

string left_shift(string a)
{
    string b;
    for(int i=1;i<a.size();i++)
    {
        b.pb(a[i]);
    }
    b.pb(a[0]);
    return b;
}

int main()
{
    int i,j,k,l;
    vector<string> keys;
    string key,intermediate="11100001100110010101010111111010101011001100111100011110",left,right,inter;
    cout<<"Enter the key:\n";
    cin>>key;
    for(i=0;i<Parity_Drop.size();i++)
    {
        intermediate.pb(key[Parity_Drop[i]-1]);
    }
    left=strip(intermediate,1);
    right=strip(intermediate,2);
    for(i=0;i<16;i++)
    {
        if(i==0 || i==1 || i==8 || i==15)
        {
            left=left_shift(left);
            right=left_shift(right);
        }
        else
        {
            left=left_shift(left_shift(left));
            right=left_shift(left_shift(right));
        }
        intermediate=left+right;
        intermediate=comp_D(intermediate);
        cout<<"Key "<<i+1<<":"<<intermediate<<endl;
        intermediate.clear();
    }
}