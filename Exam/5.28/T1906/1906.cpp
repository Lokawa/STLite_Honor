#include <queue>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=1e5+5;
struct edge
{
    int dis,to,from; 
};
bool operator<(const edge &a,const edge&b)
{
    return a.dis<b.dis;
}
edge a[N];
int f[N],n,m,k,len[N];
long long ans=0;

int find(int x)
{
    if (x==f[x]) return x;
    return f[x]=find(f[x]);
}
bool compare(int a,int b)
{
    return a>b;
}
void krustral()
{
    int t=1;
    for (int i=0;i<m;i++)
    {
        edge u=a[i];
        int x,y;
        x=find(u.from);
        y=find(u.to);
        if (x!=y)
        {
            ans+=u.dis;
            f[x]=y;
            len[t]=u.dis;
            t++;
            if (t==n) break;
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=n;i++) f[i]=i;
    for (int i=0;i<m;i++)
    {
        scanf("%d%d%d",&a[i].from,&a[i].to,&a[i].dis);
    }
    sort(a,a+m);
    krustral();
    for (int i=n-1;i>=n-k;i--)
    {
        int p=len[i];
        ans-=p;
    }
    printf("%lld\n",ans);
    system("pause");
    return 0;
}