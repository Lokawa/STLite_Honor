#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const int N=5e4+5;
int head[N],tot,low[N],dfn[N],n,m,tim,cut[N],vis[N],num,t,cnt,cas=0;
long long ans;
struct edge
{
    int next,to;
};
edge e[N*2];

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

void add(int x, int y)
{
    e[++tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

void tarjan(int u,int father)
{
    int child=0;
    dfn[u]=low[u]=++tim;
    for (int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if (!dfn[v])
        {
            child++;
            tarjan(v,u);
            low[u]=min(low[v],low[u]);
            if (low[v]>=dfn[u]) cut[u]=1;
        }
        else if (dfn[v]<dfn[u] && v!=father) low[u]=min(low[u],dfn[v]);
    }
    if (child==1 && !father) cut[u]=0;
}

void dfs(int u)
{
    vis[u]=t;
    cnt++;
    for (int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if (vis[v]!=t && cut[v]) 
        {
            num++;
            vis[v]=t;
        }
        if (!vis[v] && !cut[v]) dfs(v);
    }
}

int main()
{
    while (1)
    {
        n=read();
        if (!n) 
        {
            system("pause");
            return 0;
        }
        memset(vis,0,sizeof(vis));
        memset(cut,0,sizeof(cut));
        memset(dfn,0,sizeof(dfn));
        memset(head,0,sizeof(head));
      //  memset(low,0,sizeof(low));
        m=0;
        int sum=0;
        t=0;tot=0;tim=0;ans=1;
        for (int i=0;i<n;i++)
        {
            int x,y;
            x=read();
            y=read();
            add(x,y);
            add(y,x);
            m=max(m,max(x,y));
        }
        for (int i=1;i<=m;i++)
        {
            if (!dfn[i]) tarjan(i,0);
        }
        for (int i=1;i<=m;i++)
            if (!vis[i] && !cut[i])
            {
                t++;
                cnt=0;
                num=0;
                dfs(i);
                if (!num) sum+=2,ans*=(cnt)*(cnt-1)/2;
                if (num==1) sum++,ans*=cnt;
            }
        printf("Case %d: %d %lld\n",++cas,sum,ans);
    }
}