#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#define pb push_back
using namespace std;

string permutation(string a,vector<int> b)
{
    int i; string c;
    for(i=0;i<b.size();i++)
    {
        c.pb(a[b[i]-1]);
    }
    return c;
}
string hex2bin(string s)
{
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
    mp['A']= "1010"; 
    mp['B']= "1011"; 
    mp['C']= "1100"; 
    mp['D']= "1101"; 
    mp['E']= "1110"; 
    mp['F']= "1111"; 
    for(int i=0; i<s.size(); i++){ 
        bin+=mp[s[i]]; 
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
    mp["1010"]= "A"; 
    mp["1011"]= "B"; 
    mp["1100"]= "C"; 
    mp["1101"]= "D"; 
    mp["1110"]= "E"; 
    mp["1111"]= "F"; 
    string hex="",ch; 
    for(int i=0; i<s.length(); i+=4){ 
        ch=s.substr(i,4);
        hex+= mp[ch]; 
    } 
    return hex; 
} 

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

class key_gen
{
    private:
    string key; vector<string> keys;
    std::vector<int> Parity_Drop{ 57,49,41,33,25,17,9,1,
                        58,50,42,34,26,18,10,2,
                        59,51,43,35,27,19,11,3,
                        60,52,44,36,63,55,47,39,
                        31,23,15,7,62,54,46,38,
                        30,22,14,6,61,53,45,37,
                        29,21,13,05,28,20,12,4 };

    vector<int> Compr_D_Box{ 14, 17, 11, 24, 01, 05, 03, 28,
                        15, 06, 21, 10, 23, 19, 12, 04,
                        26, 8, 16, 07, 27, 20, 13, 02,
                        41, 52, 31 ,37, 47, 55, 30, 40,
                        51, 45, 33, 48, 44, 49, 39, 56,
                        34, 53, 46, 42, 50, 36, 29, 32 };
    public:
    key_gen()
    {
        key="01234ABCDEF56789";
        key=hex2bin(key);
    }

    string comp_D(string a)
    {
        string b;
        for(int i=0;i<Compr_D_Box.size();i++)
        {
            b.pb(a[Compr_D_Box[i]-1]);
        }
        return b;
    }

    void round_key()
    {
        int i,j,k,l;
        string intermediate,left,right,inter;
        for(i=0;i<Parity_Drop.size();i++)
        {
            intermediate.pb(key[Parity_Drop[i]-1]);
        }
        left=intermediate.substr(0,28);
        right=intermediate.substr(28,28);
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
            keys.pb(intermediate);
            cout<<"key "<<i+1<<":"<<intermediate<<endl;
            intermediate.clear();
        }
    }

    auto get_keys(){ return keys; }
    string get_key(){ return key; }
};

class encryption
{
    private:
    string plain_text,binary,ciphered;
    vector<string> keys;
    vector<int> initial_perm{ 58,50,42,34,26,18,10,2, 
                              60,52,44,36,28,20,12,4, 
                              62,54,46,38,30,22,14,6, 
                              64,56,48,40,32,24,16,8, 
                              57,49,41,33,25,17,9,1, 
                              59,51,43,35,27,19,11,3, 
                              61,53,45,37,29,21,13,5, 
                              63,55,47,39,31,23,15,7 };

    vector<int> exp_d{ 32,1,2,3,4,5,4,5, 
                       6,7,8,9,8,9,10,11, 
                       12,13,12,13,14,15,16,17, 
                       16,17,18,19,20,21,20,21, 
                       22,23,24,25,24,25,26,27, 
                       28,29,28,29,30,31,32,1};
    int s[8][4][16]={{ 
                    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7}, 
                    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8}, 
                    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
                    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
                },{ 
                    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10}, 
                    {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
                    {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15}, 
                    {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} 
                },{ 
                    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8}, 
                    {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1}, 
                    {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, 
                    {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} 
                },{ 
                    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15}, 
                    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9}, 
                    {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4}, 
                    {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} 
                },{ 
                    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9}, 
                    {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6}, 
                    {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14}, 
                    {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} 
                },{ 
                    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11}, 
                    {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8}, 
                    {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6}, 
                    {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} 
                },{ 
                    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1}, 
                    {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6}, 
                    {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2}, 
                    {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} 
                },{ 
                    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7}, 
                    {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2}, 
                    {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8}, 
                    {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} 
                }};

    vector<int> straight_per={16,7,20,21,29,12,28,17, 
                              1,15,23,26,5,18,31,10, 
                              2,8,24,14,32,27,3,9, 
                              19,13,30,6,22,11,4,25};

    vector<int> final_perm={40,8,48,16,56,24,64,32, 
                            39,7,47,15,55,23,63,31, 
                            38,6,46,14,54,22,62,30, 
                            37,5,45,13,53,21,61,29, 
                            36,4,44,12,52,20,60,28, 
                            35,3,43,11,51,19,59,27, 
                            34,2,42,10,50,18,58,26, 
                            33,1,41,9,49,17,57,25};  
    public:
    void get(vector<string> k)
    {
        cin>>plain_text;
        keys=k;
    }

    string round_function(string str,string key)
    {
        int i,row,col,val;
        string inter,inter1="";
        inter=permutation(str,exp_d);
        inter=x_or(inter,key);
        
        for(i=0;i<8;i++)
        {
            row=2*int(inter[i*6]-'0') + int(inter[i*6 +5]-'0');
            col= 8*int(inter[i*6 +1 ]-'0')+ 4*int(inter[i*6 +2]-'0')+  2*int(inter[i*6 +3]-'0')+ int(inter[i*6 +4]-'0');
            val=s[i][row][col];
            inter1+=char(val/8+'0'); val%=8;
            inter1+=char(val/4+'0'); val%=4;
            inter1+=char(val/2+'0'); val%=2;
            inter1+=char(val+'0');
        }
        inter=permutation(inter1,straight_per);
        return inter;
    }
    void convert(string plain)
    {
        int i;
        string r,intermediate,left,right,bin=hex2bin(plain);
        intermediate=permutation(bin,initial_perm);
        cout<<"After initial permutation:"<<bin2hex(intermediate)<<endl;
        left=intermediate.substr(0,32);
        right=intermediate.substr(32,32);
        for(i=0;i<15;i++)
        {
            r=right;
            right=x_or(left,round_function(right,keys[i]));
            left=r;
            cout<<"after "<<i+1<<" rounds:left->"<<bin2hex(left)<<" right->"<<bin2hex(right)<<endl;
        }
        left=x_or(left,round_function(right,keys[15]));
        cout<<"after 16 rounds:left->"<<bin2hex(left)<<" right->"<<bin2hex(right)<<endl;
        intermediate=left+right;
        intermediate=bin2hex(permutation(intermediate,final_perm));
        ciphered=intermediate;
    }

    string get_plain(){ return plain_text; }
    string get_ciphered(){ return ciphered; }
};

class decryption
{
    private:
    string decrypted; vector<string> keys;
    encryption enc;
    key_gen k;
    public:
    void get()
    {
        cout<<"Enter the ciphered text:";
        k.round_key();
        keys=k.get_keys();
        reverse(keys.begin(),keys.end());
        enc.get(keys);
    }
    void decrypt()
    {
        enc.convert(enc.get_plain());
        decrypted=enc.get_ciphered();
    }
    string get_decre()
    {
        return decrypted;
    }
};
int main()
{
    key_gen k;
    encryption e;
    decryption d;
    k.round_key();
    cout<<"Key is:"<<bin2hex(k.get_key())<<"\n\n";
    cout<<"Enter plain text:";
    e.get(k.get_keys());
    e.convert(e.get_plain());
    auto cipher=e.get_ciphered();
   
    cout<<"\nciphered string is:"<<cipher<<"\n\n";
   // d.get();
   // d.decrypt();
   // auto decipher=d.get_decre();
    //cout<<"decoded string is:"<<decipher<<endl;
}