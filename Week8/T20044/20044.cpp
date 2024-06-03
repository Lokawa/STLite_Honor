#include<iostream>
#include<cstdio>

using namespace std;

struct edge
{
    int to,next;
};

const int N=100005;
edge e[N*2];
int head[N]={0},f[N][21],d[N]={0},v[N]={0};
int tot=0,n,k,ans=0;

inline void add(int x,int y)
{
    e[++tot].to=y;
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

int find(int x,int father)
{
    int sum=0;
    for (int i=head[x];i;i=e[i].next)
    {
        int j=e[i].to;
        if (j!=father) sum+=find(j,x);
    }
    sum+=v[x];
    if (sum>ans) ans=sum;
    return sum;
}

int main()
{
    n=read();k=read();
    for (int i=0;i<n-1;i++)
    {
        int x,y,p;
        x=read();
        y=read();
        p=read();
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    for (int i=0;i<k;i++)
    {
        int x,y; 
        x=read();
        y=read();
        v[x]++;
        v[y]++;
        int m=lca(x,y);
        v[m]--;
        v[f[m][0]]--;
    }
    find(1,0);
    printf("%d\n",ans);
    system("pause");
    return 0;
}