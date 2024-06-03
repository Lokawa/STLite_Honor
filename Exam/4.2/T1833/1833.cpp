#include<iostream>
#include<cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n,v;
const int N=300005;
struct mouse
{
    int x,t,w;
    int index;
    int add,minus;
};
long long f[N]={0};
long long ask(int index)
{
    long long sum=0;
    for (int i=index;i>0;i-=i & -i)
        sum=max(sum,f[i]);
    return sum;
}
void add(int index,int v)
{
    long long p=ask(index)+v;
    for (int i=index;i<=n;i+=i & -i)
        f[i]=max(f[i],p);
}
vector<mouse> a(N);

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
int main()
{
    n=read();
    v=read();
    for (int i=1;i<=n;i++)
    {
        a[i].x=read();
        a[i].t=read();
        a[i].w=read();
        a[i].minus=v*a[i].t-a[i].x;
        a[i].add=v*a[i].t+a[i].x;
    }
    sort(a.begin()+1,a.begin()+n+1,[](mouse a,mouse b){return a.minus<b.minus;});
    int k=1;
    for (int i=1;i<=n;i++)
    {
        if (a[i].minus==a[i-1].minus) a[i].index=k; else a[i].index=++k;
    }
    sort(a.begin()+1,a.begin()+n+1,[](mouse a,mouse b){if (a.add==b.add) return a.minus<b.minus; else return a.add<b.add;});
    for (int i=1;i<=n;i++) add(a[i].index,a[i].w);
    printf("%lld\n",ask(k));
    system("pause");
    return 0;
}