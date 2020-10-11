#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<sstream>
#include<bitset>
#include<math.h>
#include<iomanip>
#define pb push_back
using namespace std;
int keys_counter=0;

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

string hex2bin(string a)
{
    // stringstream ss;
    // unsigned hex;
    // ss<<std::hex<<a;
    // ss>>hex;
    // bitset<32> b(hex);
    // return b.to_string();
    string bin=""; 
    map<char, string> mp; 
    mp['0']= "0000"; 
    mp['1']= "0001"; 
    mp['2']= "0010"; 
    mp['3']= "0011"; 
    mp['4']= "0100"; 
    mp['5']= "0101"; 
    mp['6']= "0110"; 
    mp['7']= "0111"; 
    mp['8']= "1000"; 
    mp['9']= "1001"; 
    mp['a']= "1010"; 
    mp['b']= "1011"; 
    mp['c']= "1100"; 
    mp['d']= "1101"; 
    mp['e']= "1110"; 
    mp['f']= "1111"; 
    for(int i=0; i<a.size(); i++){ 
        bin+=mp[a[i]]; 
    } 
    return bin;
}

string bin2hex(string s)
{
    map<string, string> mp; 
    mp["0000"]= "0"; 
    mp["0001"]= "1"; 
    mp["0010"]= "2"; 
    mp["0011"]= "3"; 
    mp["0100"]= "4"; 
    mp["0101"]= "5"; 
    mp["0110"]= "6"; 
    mp["0111"]= "7"; 
    mp["1000"]= "8"; 
    mp["1001"]= "9"; 
    mp["1010"]= "a"; 
    mp["1011"]= "b"; 
    mp["1100"]= "c"; 
    mp["1101"]= "d"; 
    mp["1110"]= "e"; 
    mp["1111"]= "f"; 
    string hex="",ch; 
    for(int i=0; i<s.length(); i+=4)
    { 
        ch=s.substr(i,4);
        hex+= mp[ch]; 
    } 
    return hex; 
}

string arith(string a,string b,char op)
{
    stringstream ss,ss1;
    long int a1,b1,c;
    ss<<hex<<a;
    ss>>a1;
    ss.clear();
    ss<<hex<<b;
    ss>>b1;
    ss.clear();
    if(op=='+')
    {
        c=(a1+b1) %65536;
    }
    else if(op=='*')
    {
        c=(a1*b1) %65537;
    }
    ss1<<setfill('0')<<setw(4)<<hex<<c;
    return ss1.str();
    
}

string rot_word(string a,int c)
{
    int i;
    string b="";
    for(i=c;i<a.size();i++)
    {
        b+=a[i];
    }
    for(i=0;i<c;i++)
    {
        b+=a[i];
    }
    return b;
}

class key_gen
{
    private:
    vector<string> keys;
    string key;
    public:
    void get()
    {
        //cout<<"Enter 128-bit key(hex):";
        key="11225577aabbccddeeff3344668899aa";
        key=hex2bin(key);
    }
    void generate()
    {
        int i,j;
        for(i=0;i<7;i++)
        {
            if(i==6)
            {
                for(j=0;j<64;j+=16)
                {
                    keys.pb(bin2hex(key.substr(j,16)));
                    cout<<bin2hex(key.substr(j,16))<<" ";
                }
                cout<<endl;
            }
            else
            {
                for(j=0;j<128;j+=16)
                {
                    keys.pb(bin2hex(key.substr(j,16)));
                    cout<<bin2hex(key.substr(j,16))<<" ";
                }
                cout<<"\n";
            }
            key=rot_word(key,25);
        }
    }
    auto get_keys()
    {
        return keys;
    }
};

class encrypt
{
    private:
    key_gen k;
    vector<string> keys;
    string text;
    public:
    void get_plain()
    {
        //cout<<"Enter plain text:";
        text="7869888477798669";
        k.get();
        k.generate();
        keys=k.get_keys();
    }

    string round(string p1,string p2,string p3,string p4)
    {
        string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14;
        //cout<<"p1:"<<p1<<" key:"<<keys[keys_counter]<<endl;
        // cout<<keys[keys_counter];
        s1=arith(p1,keys[keys_counter++],'*'); //1
        //cout<<"s1:"<<s1<<endl;
        // cout<<keys[keys_counter];
        s2=arith(p2,keys[keys_counter++],'+'); //2
        // cout<<keys[keys_counter];
        s3=arith(p3,keys[keys_counter++],'+'); //3
        // cout<<keys[keys_counter];
        s4=arith(p4,keys[keys_counter++],'*'); //4
        // cout<<keys[keys_counter];
        s5=bin2hex(x_or(hex2bin(s1),hex2bin(s3))); //5
        s6=bin2hex(x_or(hex2bin(s2),hex2bin(s4))); //6
        s7=arith(s5,keys[keys_counter++],'*'); //7
        // cout<<keys[keys_counter]<<endl;
        s8=arith(s6,s7,'+'); //8
        s9=arith(s8,keys[keys_counter++],'*'); //9_
        s10=arith(s7,s9,'+'); //10_
        s11=bin2hex(x_or(hex2bin(s1),hex2bin(s9)));
        s12=bin2hex(x_or(hex2bin(s3),hex2bin(s9)));
        s13=bin2hex(x_or(hex2bin(s2),hex2bin(s10)));
        s14=bin2hex(x_or(hex2bin(s4),hex2bin(s10)));
        return s11+s12+s13+s14;
    }
    string enc()
    {
        string p1,p2,p3,p4,inter;
        int i;
        p1=text.substr(0,4);
        p2=text.substr(4,4);
        p3=text.substr(8,4);
        p4=text.substr(12,4);
        for(i=0;i<8;i++)
        {
            inter=round(p1,p2,p3,p4);
            p1=inter.substr(0,4);
            p2=inter.substr(4,4);
            p3=inter.substr(8,4);
            p4=inter.substr(12,4);
            cout<<i<<":"<<inter<<endl;
        }
        p1=arith(p1,keys[keys_counter++],'*');
        string p2_=arith(p3,keys[keys_counter++],'+');
        string p3_=arith(p2,keys[keys_counter++],'+');
        p4=arith(p4,keys[keys_counter++],'*');
        return p1+p2_+p3_+p4;
    }
};
int main()
{
    // key_gen k;
    // k.get();
    // k.generate();
    // auto k1=k.get_keys();
    // for(auto it:k1)
    // {
    //     cout<<it<<endl;
    // }
    
    encrypt e;
    e.get_plain();
    auto cipher=e.enc();
    cout<<cipher<<endl;
}