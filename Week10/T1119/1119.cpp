#include<iostream>
#include<cstdio>
const int N=1e5+5;
int n,m;
long double sum[N<<2],squ[N<<2],lazy[N<<2],a[N];

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

void pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    squ[rt]=squ[rt<<1]+squ[rt<<1|1];
}

void build(int rt,int l,int r)
{
    if (l==r) 
    {
        sum[rt]=a[l];
        squ[rt]=a[l]*a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1 | 1,mid+1,r);
    pushup(rt);
}

void change(int rt,int l,int r,double z)
{
    squ[rt]+=z*2*sum[rt]+(r-l+1)*z*z;
    sum[rt]+=(r-l+1)*z;
}

void pushdown(int rt, int l,int r)
{
    if (lazy[rt]==0) return;
    if (l==r)
    {
        lazy[rt]==0;
        return;
    }
    lazy[rt<<1]+=lazy[rt];
    lazy[rt<<1|1]+=lazy[rt];
    int mid=(l+r)>>1;
    change(rt<<1,l,mid,lazy[rt]);
    change(rt<<1|1,mid+1,r,lazy[rt]);
    lazy[rt]=0;
}

void update(int rt,int l,int r,int x,int y,double z)
{
    pushdown(rt,l,r);
    if (x<=l && r<=y)
    {
        lazy[rt]+=z;
        change(rt,l,r,z);
        return;
    }
    int mid=(l+r)>>1;
    if (x<=mid) update(rt<<1,l,mid,x,y,z);
    if (y>mid) update(rt<<1|1,mid+1,r,x,y,z);
    pushup(rt);
}

double query_sum(int rt,int l,int r,int x,int y)
{
    pushdown(rt,l,r);
    if (x<=l && r<=y) return sum[rt];
    int mid=(l+r)>>1;
    if (y<=mid) return query_sum(rt<<1,l,mid,x,y);
    if (x>mid) return query_sum(rt<<1|1,mid+1,r,x,y);
    return query_sum(rt<<1,l,mid,x,y)+query_sum(rt<<1|1,mid+1,r,x,y);
}
double query_squ(int rt,int l,int r,int x,int y)
{
    pushdown(rt,l,r);
    if (x<=l && r<=y) return squ[rt];
    int mid=(l+r)>>1;
    if (y<=mid) return query_squ(rt<<1,l,mid,x,y);
    if (x>mid) return query_squ(rt<<1|1,mid+1,r,x,y);
    return query_squ(rt<<1,l,mid,x,y)+query_squ(rt<<1|1,mid+1,r,x,y);
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%llf",a+i);
    build(1,1,n);
    for (int i=0;i<m;i++)
    {
        int sign,x,y; 
        long double k;
        sign=read();x=read();y=read();
        if (sign==1) 
        {
            scanf("%llf",&k);
            update(1,1,n,x,y,k);
        }
        else if (sign==2)
        {
            k=query_sum(1,1,n,x,y)*100/(y-x+1);
            printf("%d\n",(int)k);
        }
        else
        {
            long double p=query_sum(1,1,n,x,y)/(y-x+1);
            k=(query_squ(1,1,n,x,y)/(y-x+1)-p*p)*100;
            printf("%d\n",(int)k);
        }
    }
    system("pause");
    return 0;
}