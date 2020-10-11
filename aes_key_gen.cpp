#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<sstream>
#include<bitset>
#define pb push_back
using namespace std;

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

string SubByte(vector<string> sBox,string a)
{
    stringstream ss;
    int i,row,col;
    string b="";
    for(i=0;i<8;i+=2)
    {
        ss<<hex<<a[i];
        ss>>row;
        ss.clear();
        ss<<hex<<a[i+1];
        ss>>col;
        ss.clear();
        b+=sBox[(16*row)+col];
    }
    return b;
}

string hex2bin(string a)
{
    stringstream ss;
    unsigned hex;
    ss<<std::hex<<a;
    ss>>hex;
    bitset<32> b(hex);
    return b.to_string();
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
    for(int i=0; i<s.length(); i+=4)
    { 
        ch=s.substr(i,4);
        hex+= mp[ch]; 
    } 
    return hex; 
}

string rot_word(string a)
{
    int i;
    string b="";
    for(i=2;i<a.size();i++)
    {
        b+=a[i];
    }
    b+=a[0]; b+=a[1];
    return b;
}

class aes_key
{
    private:
    string key;
    vector<string> exp_keys;
    vector<string> s_box={ "63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76",
                        "CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0",
                        "B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15",
                        "04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75",
                        "09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84",
                        "53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF",
                        "D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8",
                        "51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2",
                        "CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73",
                        "60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB",
                        "E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79",
                        "E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08",
                        "BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A",
                        "70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E",
                        "E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF",
                        "8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16" };
    
    vector<string> RCon={ "01000000","02000000","04000000","08000000",
                          "10000000","20000000","40000000","80000000",
                          "1B000000","36000000" };
    public:
    void get()
    {
        cout<<"Enter 4-word key:\n";
        for(int i=0;i<4;i++)
        {
            cin>>key;
            exp_keys.pb(key);
        }
    }

    void expand()
    {
        int i,j=0;
        string inter;
        for(i=4;exp_keys.size()!=44;i++)
        {
            
            if(!(i%4))
            {
                inter=SubByte(s_box,rot_word(exp_keys[i-1]));
                inter=bin2hex(x_or(x_or(hex2bin(inter),hex2bin(exp_keys[i-4])),hex2bin(RCon[j++])));
                exp_keys.pb(inter);
            }
            else
            {
                inter=bin2hex(x_or(hex2bin(exp_keys[i-1]),hex2bin(exp_keys[i-4])));
                exp_keys.pb(inter);
            }
            
        }
    }

    vector<string> get_keys() { return exp_keys; }
    vector<string> get_s() { return s_box; }
};

int main()
{
    aes_key k;
    k.get();
    k.expand();
    auto keys=k.get_keys();
    cout<<"\n\n"; 
    for(int i=0;i<keys.size();i+=4)
    {
        cout<<"round "<<i/4<<":"<<keys[i]<<keys[i+1]<<keys[i+2]<<keys[i+3]<<endl;
    }
}