#include <iostream>
#include <cstdio>

using namespace std;
struct edge
{
    int next,to;
};
const int N=5e5+5;
int f[N][21]={0},d[N]={0},head[N]={0},tot=0,v[N]={0};
edge e[2*N];
int a,b,c,n,m;;

void add(int x,int y)
{
    e[++tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

int dfs(int x,int father)
{
    d[x]=d[father]+1;
    f[x][0]=father;
    for (int i=1;(1<<i)<=d[x];i++) 
    {
        f[x][i]=f[f[x][i-1]][i-1];
    }
    for (int i=head[x];i;i=e[i].next)
    {
        int j=e[i].to;
        if (j!=father) v[x]+=dfs(j,x);
    }
    v[x]++;
    return v[x];
}

inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int lca(int x,int y)
{
    if (d[x]<d[y])
    {
        int t=x;
        x=y;
        y=t;
    }
    for (int i=20;i>=0;i--)
    {
        if (d[f[x][i]]>=d[y]) x=f[x][i];
    }
    if (x==y) return x;
    for (int i=20;i>=0;i--)
    {
        if (f[x][i]!=f[y][i])
        {
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}

int llca(int x,int y)
{   
    for (int i=20;i>=0;i--)
    {
        if (d[f[x][i]]>d[y])
        {
            x=f[x][i];
        }
    }
    return x;
}

void find(int m)
{
    if (a==b) 
    {
        if (a==c) printf("%d\n",n); else printf("%d\n",0);
        return;
    }
    if (a==m || b==m)
    {
        if (d[a]<d[b]) swap(a,b);
        if (d[c]<d[b]|| d[c]>d[a]) printf("%d\n",0);
        else if (a==c) printf("%d\n",v[a]);
        else if (b==c) printf("%d\n",n-v[llca(a,m)]);
        else
        {
            int x=llca(a,c);
            if (f[x][0]==c) printf("%d\n",v[c]-v[x]); else printf("%d\n",0);
        }
        return;
    }
    if (d[c]<d[m] || d[c]>max(d[a],d[b])) 
    {
        printf("%d\n",0);
        return;
    }
    if (m==c)
    {
        printf("%d\n", n-v[llca(a,c)]-v[llca(b,c)]);
        return;
    } 
    if (a==c)
    {
        printf("%d\n",v[a]);
        return;
    }
    if (b==c)
    {
        printf("%d\n",v[b]);
        return;
    }
    int x=llca(a,c);
    if (f[x][0]==c)
    {
        printf("%d\n",v[c]-v[x]);
        return;
    }
    int y=llca(b,c);
    if (f[y][0]==c)
    {
        printf("%d\n",v[c]-v[y]);
        return;
    }
    printf("%d\n",0);
}
int main()
{
    cin>>n>>m;
    for (int i=0;i<n-1;i++)
    {
        int x,y;
        x=read();
        y=read();
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    for (int i=0;i<m;i++)
    {
        a=read();
        b=read();
        c=read();
        int x=lca(a,b);
        find(x);
    }
    system("pause");
    return 0;
}