#include<iostream>
#include<cstdio>
#include<string>
#include<set>

using namespace std;
const int mod1=1e7+7;
const int mod2=1e7+9;
const int base1=13;
const int base2=233;
struct Hash
{
    int hash1,hash2;
    Hash()
    {
        hash1=0;
        hash2=0;
    }
};
bool operator<(const Hash &a,const Hash &b)
{
    if (a.hash1<b.hash1 || a.hash1==b.hash1 && a.hash2<b.hash2) return 1; else return 0;
}
int main()
{
    int n,m;
    char s[1000000];
    set<Hash> substring;
    cin>>n>>m;
    Hash *H,power;
    H=new Hash [n+1];
    cin>>s;
    power.hash1=1;
    power.hash2=1;
    H[0].hash1=s[0]%mod1;
    H[0].hash2=s[0]%mod2;
    for (int i=1;i<n;i++)
    {
        H[i].hash1=((long long)H[i-1].hash1*base1+s[i])%mod1;
        H[i].hash2=((long long)H[i-1].hash2*base2+s[i])%mod2;
    }
    for (int i=1;i<=m;i++)
    {
        power.hash1=((long long)power.hash1*base1)%mod1;
        power.hash2=((long long)power.hash2*base2)%mod2;
    }
    for (int i=1;i<n-m+1;i++) 
    {
        Hash t;
        t.hash1=((long long)H[i+m-1].hash1-(long long)H[i-1].hash1*power.hash1%mod1+mod1)%mod1;
        t.hash2=((long long)H[i+m-1].hash2-(long long)H[i-1].hash2*power.hash2%mod2+mod2)%mod2;
        substring.insert(t);
    }
    Hash t;
    t.hash1=0;
    t.hash2=0;
    for (int i=0;i<m;i++)
    {
        t.hash1=((long long)t.hash1*base1+s[i])%mod1;
        t.hash2=((long long)t.hash2*base2+s[i])%mod2;
    }
    substring.insert(t);
    cout<<substring.size()<<endl;
    system("pause");
    delete []H;
    return 0;
}