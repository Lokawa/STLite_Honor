#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;
const int mod=1e9+7;
const int base=13;
int main()
{
    int n;
    cin>>n;
    long long *hash,*power;
    hash=new long long [n];
    power=new long long [n];
    long long f=-1;
    int num=0;
    for (int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        hash[i]=0;
        power[i]=1;
        int j=0;
        int k=0;
        while (j<s.size())
        {
            if (s[j]!='{' && s[j]!='}') 
            {
                hash[i]=((long long)hash[i]*base+s[j])%mod;
                power[i]=((long long )power[i]*base)%mod;
                j++;
            }
            if (s[j]=='{') 
            {
                j++; 
                k=0;
                while (s[j]!='}')
                {
                    k=k*10+s[j]-48;
                    j++;
                }
                j++;
                power[i]=((long long)power[i]*power[k])%mod;
                hash[i]=((long long)hash[i]*power[k]%mod+hash[k])%mod;
            }
        }
        if (hash[i]!=f)
        {
            f=hash[i];
            num++;
        }
    }
    cout<<num<<endl;
    system("pause");
    return 0;
}