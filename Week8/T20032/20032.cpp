#include<iostream>
#include<cstdio>

using namespace std;

struct edge
{
    int to,w,next;
};

const int N=50005;
edge e[N*2];
int head[N]={0},f[N][21],d[N]={0},v[N]={0};
int tot=0,n,m,q;

inline void add(int x,int y,int w)
{
    e[++tot].to=y;
    e[tot].w=w;
    e[tot].next=head[x];
    head[x]=tot;
}

void dfs(int x,int father)
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
        if (j!=father)
        {
            v[j]=v[x]+e[i].w;
            dfs(j,x);
        }
    }
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

inline int read() {                 // read in a int and return
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

int main()
{
    cin>>n;
    for (int i=0;i<n-1;i++)
    {
        int a,b,c;
        a=read();b=read();c=read();
        add(a,b,c);
        add(b,a,c);
    }
    q=read();
    dfs(1,0);
    for (int i=0;i<q;i++)
    {
        int x,y,z,ans=0;
        x=read();
        y=read();
        z=read();
        int l1=lca(x,y),l2=lca(x,z),l3=lca(y,z);
        if (d[l1]>=d[l2] && d[l1]>=d[l3])
        {
            int p=lca(l1,z);
            ans=v[x]+v[y]-2*v[l1]+v[z]+v[l1]-2*v[p];
            printf("%d\n",ans);
        }
        else if (d[l2]>=d[l1] && d[l2]>=d[l3])
        {
            int p=lca(l2,y);
            ans=v[x]+v[z]-2*v[l2]+v[l2]+v[y]-2*v[p];
            printf("%d\n",ans);
        }
        else if (d[l3]>=d[l2] && d[l3]>=d[l1])
        {
            int p=lca(l3,x);
            ans=v[y]+v[z]-2*v[l3]+v[l3]+v[x]-2*v[p];
            printf("%d\n",ans);
        }
    }
    system("pause");
    return 0;
}