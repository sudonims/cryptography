#include<iostream>
#include<sstream>
#include<bitset>
#include<algorithm>
#include<vector>
#include<math.h>
#include<iomanip>
#include<fstream>
using namespace std;

// namespace nim{
// class stringstream
// {

// };
// }
int main()
{
    // string a="12345678";
    // unsigned c;
    // std::stringstream ss;
    // ss<<hex<<a;
    // ss>>c;
    // bitset<36> b(c);
    // cout<<b.to_string();
    // string a="1F2F";
    // int b;
    // stringstream ss;
    // ss<<hex<<a;
    // ss>>b;
    // cout<<b;

    // stringstream ss;
    // int a=65536;
    // ss<<setfill('0')<<setw(4)<<hex<<a;
    // cout<<ss.str();

    // int c=pow(2,16);
    // cout<<c;
    // string a="NEXTMOVE"; int b;
    // for(int i=0;i<a.size();i++)
    // {
    //     b=a[i];
    //     cout<<b;
    // }
    // stringstream ss;
    // int c=65535;
    // ss<<hex<<c;
    // cout<<ss.str();
    string str;
	ifstream infile;
	infile.open("Keyfile", ios::in | ios::binary);

	if (infile.is_open())
	{
		getline(infile, str); // The first line of file should be the key
		infile.close();
	}

    cout<<str<<endl;
    istringstream ss(str);
    unsigned char key[16];
	int i = 0;
	int c;
    for(i=0;i<16;i++)
	{
		ss >>hex>> c;
        cout<<c;
        key[i] = c;
        cout<<key[i]<<",";
	}
    unsigned char *a;
    cin>>a;
    cout<<'\n'<<a;
}