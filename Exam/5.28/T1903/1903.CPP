#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

struct edge
{
    int to,w,next;
};
const int N=5e3+7;
int head[N],vis[N],n,m,s,t,tot=0;
bool flag=false;
long long dis[N];
edge e[N<<1];

void add(int x,int y,int w)
{
    e[++tot].to=y;
    e[tot].next=head[x];
    e[tot].w=w;
    head[x]=tot;
}

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

int main()
{
    n=read();
    m=read();
    s=read();
    t=read();
    memset(dis,0x3f3f3f3f,sizeof(dis));
    memset(head,0,sizeof(head));
    memset(vis,0,sizeof(vis));
    for (int i=0;i<m;i++)
    {
        int x,y,w;
        x=read();y=read();w=read();
        add(x,y,w);
    }
    dis[s]=0;
    queue<int> a;
    a.push(s);
    while (!a.empty())
    {
        int p=a.front();
        a.pop();
        for (int i=head[p];i;i=e[i].next)
        {
            int v=e[i].to;
            if (v==t && flag)
            {
                printf("1\n");
                system("pause");
                return 0;
            }
            if (vis[v]>n) continue;
            if (dis[p]+e[i].w<dis[v])
            {
                dis[v]=e[i].w+dis[p];
                vis[v]++;
                a.push(v);
                if (vis[v]>n) flag=true;
            }
        }
    }
    printf("0\n");
    system("pause");
    return 0;
}