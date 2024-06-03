#include<iostream>
#include<cstdio>
#include<cmath>

const int N=1e5+5;
int n,height[N<<2]={0},lazy[N<<2],a[N];
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
void pushup(int rt)
{
    height[rt]=std::max(height[rt<<1],height[rt<<1|1]);
}
void pushdown(int rt,int l,int r)
{
    if (!lazy[rt] || l==r) return;
    height[rt<<1]=height[rt<<1|1]=lazy[rt];
    lazy[rt<<1]=lazy[rt<<1|1]=lazy[rt];
    lazy[rt]=0;
}
void update(int rt,int l,int r,int x,int y,int h)
{
    
    if (x<=l && r<=y && h>height[rt])
    {
        height[rt]=h;
        lazy[rt]=h;
        if (l==r) a[l]=h;
        return;
    }
    if (l==r) return;
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if (x<=mid) update(rt<<1,l,mid,x,y,h);
    if (y>mid) update(rt<<1|1,mid+1,r,x,y,h);
    pushup(rt);
}

void query(int rt,int l,int r)
{
    if (l==r)
    {
        a[l]=height[rt];
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    query(rt<<1,l,mid);
    query(rt<<1|1,mid+1,r);
}

int main()
{
    n=read();
    for (int i=0;i<n;i++)
    {
        int x,y,h;
        x=read();h=read();y=read()-1;
        update(1,0,N-1,x,y,h);
    }
    query(1,0,N-1);
    for (int i=1;i<N;i++)
        if (a[i]!=a[i-1]) printf("%d %d\n",i,a[i]);
    system("pause");
    return 0;
}