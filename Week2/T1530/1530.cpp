#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>

using namespace std;

const int mod = 1e7 + 7;
const int base = 139;
int Hash(const string &s)
{
    int hash=0;
    for (int i=0;i<s.size();i++)
        hash=((long long)hash*base+s[i])%mod;
    return hash;
}
int main()
{
    int n,m,i;
    cin>>n;
    bool *hash;
    hash=new bool[mod];
    memset(hash,false,mod);
    for (i=0;i<n;i++) 
    {   
        string s;
        cin>>s;
        hash[Hash(s)]=true;
    }
    int *H;
    H=new int [mod];
    memset(H,0,mod);
    cin>>m;
    int *text;
    text=new int[m];
    int top=0,num=0,len=m,max=0;
    for (i=0;i<m;i++)
    {
        string s;
        cin>>s;
        text[i]=Hash(s);
        H[text[i]]++;
        if (H[text[i]]==1 && hash[text[i]]) max++;
    }
    cout<<max<<endl;
    delete []H;
    H=new int[mod];
    memset(H,0,mod);
    for (i=0;i<m;i++)
    {
        H[text[i]]++;
        if (H[text[i]]==1 && hash[text[i]]) num++;
        while (num==max)
        {
            if (i-top+1<len) len=i-top+1;
            H[text[top]]--;
            if (H[text[top]]==0 && hash[text[top]]) num--;
            top++;
        }
    }
    if (max!=0) cout<<len<<endl; else cout<<0<<endl;
    delete []H;
    delete []hash;
    delete []text;
    system("pause");
    return 0;
}