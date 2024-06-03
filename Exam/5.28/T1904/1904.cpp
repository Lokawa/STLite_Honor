#include<iostream>
#include<cstdio>
#include<stack>
#include<cstring>
using namespace std;
const int N=5e3+5;
int dfn[N],low[N],sizee[N],depth,group[N],sum,s[N],n;
bool vis[N],fin[N]={0},f[N][N]={0};
stack<int> stackk;
struct beat
{
    int enemy[N];
    int tot;
};
beat a[N];

void tarjan(int u)
{
    dfn[u]=++depth;
    low[u]=dfn[u];
    vis[u]=1;
    stackk.push(u);
    for (int i=0;i<a[u].tot;i++)
    {
        int v=a[u].enemy[i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[v],low[u]);
        }
        else if (vis[v])
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (dfn[u]==low[u])
    {
        group[u]=++sum;
        vis[u]=0;
        while (stackk.top()!=u)
        {
            group[stackk.top()]=sum;
            vis[stackk.top()]=0;
            s[sum]++;
            stackk.pop();
        }
        stackk.pop();
        s[sum]++;
    }
}

void dfs(int u)
{
    vis[u]=true;
    if (fin[u]) return;
    for (int i=1;i<=sum;i++)
    {
        if (f[u][i] && !vis[i])
        {
            dfs(i);
            sizee[u]+=s[i];
        }
    }
    sizee[u]+=s[u];
    fin[u]=1;
}


int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        char ch='\0';
        for (int j=1;j<=n;j++) 
        {
            do ch=getchar(); while (ch!='0' && ch!='1');
            if (ch=='1')
            {
                a[i].enemy[a[i].tot++]=j;
            }
        }
    }
    for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);

    for (int i=1;i<=n;i++)
        for (int j=0;j<a[i].tot;j++)
        {
            int v=a[i].enemy[j];
            if (group[i]!=group[v]) f[group[i]][group[v]]=1;
        }
    for (int i=1;i<=sum;i++)
    {
        if (!fin[i])
        {
            memset(vis,0,sizeof(vis));
            dfs(i);
        }
    }
    for (int i=1;i<=n;i++) printf("%d\n",sizee[group[i]]-1);
    system("pause");
    return 0;
}