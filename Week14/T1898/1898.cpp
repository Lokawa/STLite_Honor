#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

struct edge
{
    int from, to ,dis;
};
struct Edge
{
   int to,next,dis;
};

const int N=5e4+5;
edge e[N];
Edge a[N<<1];
int head[N]={0},f[N]={0},fa[N][21],w[N][21],tot,deep[N]={0},n,m;
void add(int from,int to, int dis)
{
    a[++tot].next=head[from];
    a[tot].to=to;
    a[tot].dis=dis;
    head[from]=tot;
}
int find(int x)
{
    if (x!=f[x]) f[x]=find(f[x]);
    return f[x];
}

void kruskal()
{
    int t=n;
    for (int i=1;i<=m;i++)
    {
        if (find(e[i].from)!=find(e[i].to))
        {
            add(e[i].from,e[i].to,e[i].dis);
            add(e[i].to,e[i].from,e[i].dis);
            t--;
            f[find(e[i].from)]=find(e[i].to);
            if (t==1) break;
        }
    }
}

void dfs(int u,int father,int dis)
{
    deep[u]=deep[father]+1;
    fa[u][0]=father;
    w[u][0]=dis;
    for (int i=1;(1<<i)<=deep[u];i++)
    {
        fa[u][i]=fa[fa[u][i-1]][i-1];
        w[u][i]=std::min(w[u][i-1],w[fa[u][i-1]][i-1]);
    }
    for (int i=head[u];i;i=a[i].next)
    {
        if (a[i].to!=father)
        {
            dfs(a[i].to,u,a[i].dis);
        }
    }
}

int lca(int x,int y)
{
    if (deep[x]<deep[y]) std::swap(x,y);
    int ans=1e9;
    while (deep[x]>deep[y])
    {
        for (int i=log2(deep[x]-deep[y]);i>=0;i--)
            if (deep[fa[x][i]]>=deep[y]) 
            {
                ans=std::min(ans,w[x][i]);
                x=fa[x][i];
            }
    }
    if (x==y) return ans;
    for (int k=log2(deep[x]);k>=0;k--)
    {
        if (fa[x][k]!=fa[y][k])
        {
            ans=std::min(ans,w[x][k]);
            x=fa[x][k];
            ans=std::min(ans,w[y][k]);
            y=fa[y][k];
        }
    }
    ans=std::min(ans,std::min(w[x][0],w[y][0]));
    return ans;
}
void sort(int l,int r)
{
    edge mid=e[(l+r)/2];
    int i=l,j=r;
    while (i<=j)
    {
        while (e[i].dis>mid.dis) i++;
        while (e[j].dis<mid.dis) j--;
        if (i<=j)
        {
            edge tmp;
            tmp=e[i];e[i]=e[j]; e[j]=tmp;
            i++;j--;
        }
    }
    if (i<r) sort(i,r);
    if (j>l) sort(l,j);
}
int main()
{
    n=read();m=read();
    for (int i=1;i<n;i++) f[i]=i;
    for (int i=1;i<=m;i++)
    {
        e[i].from=read();e[i].to=read();e[i].dis=read();
    }
    tot=0;
    memset(w, 0x3f3f3f3f,sizeof(w));
    sort(1,m);
    kruskal();
    for (int i=1;i<=n;i++)
    {
        if (deep[i]==0) dfs(i,0,0);
    }
    int q=read();
    for (int i=0;i<q;i++)
    {
        int x,y;
        x=read();y=read();
        if (find(x)==find(y)) printf("%d\n",lca(x,y)); else printf("-1\n");
    }
    system("pause");
    return 0;
}