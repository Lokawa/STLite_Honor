#include<iostream>
#include<cstdio>

using namespace std;

const int N=1e6+5;
int tot=0;
int f[N][28]={0},fail[N]={0};
bool flag[N]={0};
string str;

void bfs(int x)
{
    int prev;
    for (int i=0;i<26;i++)
    {
        if (!f[x][i]) continue;
        int c=f[x][i];
        prev=fail[x];
        while (f[prev][i]==0 && prev!=-1) prev=fail[prev];
        if (prev!=-1) fail[c]=f[prev][i];
    }
    for (int i=0;i<26;i++)
    {
        if (f[x][i]) bfs(f[x][i]);
    }
}

bool check()
{
    int targetcursor=0,sourcecursor=0;
    int len=str.size();
    while (sourcecursor<len && !flag[targetcursor])
    {
        if (targetcursor==-1) targetcursor=0;
        if (f[targetcursor][str[sourcecursor]-'a'])
        {
            targetcursor=f[targetcursor][str[sourcecursor]-'a'];
            sourcecursor++;
        }
        else if (targetcursor==0) sourcecursor++;
        else targetcursor=fail[targetcursor];
    }
    return flag[targetcursor];
}

int main()
{
    int n;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        string ch;
        cin>>ch;
        int root=0;
        for (int j=0;j<ch.size();j++)
        {
            int id=ch[j]-'a';
            if (!f[root][id]) f[root][id]=++tot;
            root=f[root][id];
        }
        flag[root]=true;
    }
    fail[0]=-1;
    bfs(1);
    cin>>str;
    if (check()) cout<<"valar morghulis"<<endl; else cout<<"valar dohaeris"<<endl;
    system("pause");
    return 0;
}