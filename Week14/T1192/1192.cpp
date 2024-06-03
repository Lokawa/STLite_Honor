#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;


int n,m,dis[1002],d[1002][1002];
bool f[1002]={0};
void dijkstra(int k)
{
    dis[k]=0;
    int maxn,t;
    for (int i=0;i<m;i++)
    {
        maxn=9e8+9;
        for (int j=0;j<m;j++)
        {
            if (!f[j] && dis[j]<maxn)
            {
                maxn=dis[j];
                t=j;
            }
        }
        f[t]=1;
        for (int j=0;j<m;j++)
        {
            dis[j]=min(dis[t]+d[t][j],dis[j]);
        }
    } 
}

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
struct point
{
    int x,y,color;
};
point a[1002];

int main()
{
    int begin,end;
    bool flag=false;
    memset(d,1,sizeof(d));
    memset(dis,1,sizeof(dis));
    n=read();
    m=read();
    for (int i=0;i<m;i++)
    {
        a[i].x=read();
        a[i].y=read();
        a[i].color=read();
        if (a[i].x==1 && a[i].y==1) begin=i;
        if (a[i].x==n && a[i].y==n)
        {
            end=i;
            flag=true;
        }
    }
    if (!flag)
    {
        end=m;
        a[end].x=n;
        a[end].y=n;
    }
    for (int i=0;i<m;i++)
    {
        for (int j=i+1;j<m;j++)
        {
            if (abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y)==1) 
            {
                d[i][j]=abs(a[i].color-a[j].color);
                d[j][i]=d[i][j];
            }
            else if (abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y)==2) 
            {
                d[i][j]=abs(a[i].color-a[j].color)+2;
                d[j][i]=d[i][j];
            }
        }
    }
    if (!flag)
    {
        for (int i=0;i<m;i++)
        {
            if (abs(a[i].x-a[end].x)+abs(a[i].y-a[end].y)==1)
            {
                d[i][end]=2;
                d[end][i]=2;
            }
        }
        m++;
    }
    dijkstra(begin);
    if (dis[end]<5e5+5) printf("%d\n",dis[end]); else printf("-1\n");
    system("pause");
    return 0;
}