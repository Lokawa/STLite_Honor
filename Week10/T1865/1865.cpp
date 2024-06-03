#include<iostream>
#include<cstdio>

const int N=1e5+5;
long long a[N],sum[N<<2],plazy[N<<2]={0},mlazy[N<<2];
long long n,m,p;

inline long long read()
{
    long long x = 0,f = 1;char ch = getchar();
    while(ch<'0' || ch>'9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch>='0' && ch<='9'){x = x*10 + ch - '0';ch = getchar();}
    return x*f;
}
void pushup(long long rt)
{
    sum[rt]=(sum[rt<<1]+sum[rt<<1|1])%p;
}

void build(long long rt,long long l,long long r)
{
    if (l==r)
    {
        sum[rt]=a[l]%p;
        return;
    }
    mlazy[rt]=1;
    long long mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void pushdown(long long rt,long long l,long long r)
{
    if (mlazy[rt]==1 && plazy[rt]==0 || l==r) return;
    long long mid=(l+r)>>1,mul=mlazy[rt],plus=plazy[rt];
    sum[rt<<1]=(sum[rt<<1]*mul+plus*(mid-l+1)%p)%p;
    sum[rt<<1|1]=(sum[rt<<1|1]*mul+plus*(r-mid)%p)%p;
    plazy[rt<<1]=(plazy[rt<<1]*mul+plus)%p;
    plazy[rt<<1|1]=(plazy[rt<<1|1]*mul+plus)%p;
    mlazy[rt<<1]=mlazy[rt<<1]*mul%p;
    mlazy[rt<<1|1]=mlazy[rt<<1|1]*mul%p;
    mlazy[rt]=1;
    plazy[rt]=0;
}
void add(long long rt,long long l,long long r,long long x,long long y,long long z)
{
    if (x<=l && r<=y)
    {
        plazy[rt]=(plazy[rt]+z)%p;
        sum[rt]=(sum[rt]+(r-l+1)*z)%p;
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if (x<=mid) add(rt<<1,l,mid,x,y,z);
    if (y>mid) add(rt<<1|1,mid+1,r,x,y,z);
    pushup(rt);
}
void mult(long long rt,long long l,long long r,long long x,long long y,long long z)
{
    if (x<=l && r<=y)
    {
        mlazy[rt]=mlazy[rt]*z%p;
        plazy[rt]=plazy[rt]*z%p;
        sum[rt]=sum[rt]*z%p;
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if (x<=mid) mult(rt<<1, l,mid,x,y,z);
    if (y>mid) mult(rt<<1|1,mid+1,r,x,y,z);
    pushup(rt);
}
long long query(long long rt,long long l,long long r,long long x,long long y)
{
    pushdown(rt,l,r);
    if (x<=l && r<=y) return sum[rt];
    int mid=(l+r)>>1;
    if (y<=mid) return query(rt<<1,l,mid,x,y);
    if (x>mid) return query(rt<<1|1,mid+1,r,x,y);
    return (query(rt<<1,l,mid,x,y)+query(rt<<1|1,mid+1,r,x,y))%p;
}
int main()
{
    n=read();p=read();
    for (int i=0;i<(N<<2);i++) mlazy[i]=1;
    for (int i=1;i<=n;i++) a[i]=read();
    m=read();
    build(1,1,n);
    for (int i=0;i<m;i++)
    {  
        long long sign,l,r,x;
        sign=read();l=read();r=read();
        if (sign==1) 
        {
            x=read();
            mult(1,1,n,l,r,x);
        }
        else if (sign==2)
        {
            x=read();
            add(1,1,n,l,r,x);
        }
        else
        {
            printf("%lld\n",query(1,1,n,l,r)%p);
        }
    }
    system("pause");
    return 0;
}