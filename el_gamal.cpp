#include<iostream>
#include<algorithm>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
bool isPrime(int n) 
{
	if (n <= 1) return false; 
	if (n <= 3) return true; 
	if (n%2 == 0 || n%3 == 0) return false; 

	for (int i=5; i*i<=n; i=i+6) 
		if (n%i == 0 || n%(i+2) == 0) 
			return false; 

	return true; 
} 
int power(int x, unsigned int y, int p) 
{ 
	int res = 1;	 // Initialize result 

	x = x % p;

	while (y > 0) 
	{ 
		if (y & 1) 
			res = (res*x) % p; 

		y = y >> 1; // y = y/2 
		x = (x*x) % p; 
	} 
	return res; 
} 
void findPrimefactors(unordered_set<int> &s, int n) 
{ 
	while (n%2 == 0) 
	{ 
		s.insert(2); 
		n = n/2; 
	} 
	for (int i = 3; i <= sqrt(n); i = i+2) 
	{ 
		while (n%i == 0) 
		{ 
			s.insert(i); 
			n = n/i; 
		} 
	} 
	if (n > 2) 
		s.insert(n); 
} 
int findPrimitive(int n) 
{ 
	unordered_set<int> s; 
	if (isPrime(n)==false) 
		return -1; 
	int phi = n-1; 
	findPrimefactors(s, phi); 
	for (int r=2; r<=phi; r++) 
	{ 
		bool flag = false; 
		for (auto it = s.begin(); it != s.end(); it++) 
		{ 
			if (power(r, phi/(*it), n) == 1) 
			{ 
				flag = true; 
				break; 
			} 
		} 
		if (flag == false) 
		return r; 
	} 
	return -1; 
}

size_t inver_modulo(size_t a,size_t mod)
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
    size_t k,K,msg,xa,prime,q,alpha,ya;
    cout<<"Enter msg and mod/prime and xa:";
    cin>>msg>>prime>>xa;
    alpha=findPrimitive(prime);
    ya=pow(alpha,xa);
    ya%=prime;
    cout<<"private key:"<<xa<<" public key:("<<prime<<","<<alpha<<","<<ya<<")\n";
    cout<<"Enter k <mod :";
    cin>>k;
    K=pow(ya,k);
    K%=prime;
    cout<<"One time key:"<<K<<endl;
    size_t c1,c2;
    c1=pow(alpha,k); c1%=prime;
    c2=(K*msg)%prime;
    cout<<"Encrypted msg:("<<c1<<","<<c2<<")\n";

    K=pow(c1,xa);
    K%=prime;
    cout<<K<<endl;
    size_t M;
    M=((c2%prime) * (inver_modulo(K,prime)))%prime;
    cout<<"Decrypted  msg:"<<M<<endl;
}