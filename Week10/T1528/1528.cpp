#include<iostream>
#include<cstdio>
#include<cmath>
struct room
{
    int left,right,len;
};

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

const int N=5e5+5;
int lazy[N<<2],n,m;
room f[N<<2];

void pushup(int rt,int l,int r)
{
    int mid=(l+r)>>1;
    f[rt].len=std::max(f[rt<<1].right+f[rt<<1|1].left,std::max(f[rt<<1].len,f[rt<<1|1].len));
    f[rt].left=f[rt<<1].left;
    if (f[rt].left==mid-l+1) f[rt].left+=f[rt<<1|1].left;
    f[rt].right=f[rt<<1|1].right;
    if (f[rt].right==r-mid) f[rt].right+=f[rt<<1].right;
}
void build(int rt,int l,int r)
{
    f[rt].len=r-l+1;
    f[rt].right=f[rt].left=r-l+1;
    lazy[rt]=-1;
    if (l==r) return;
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
void pushdown(int rt,int l,int r)
{
    if (l==r) return;
    if (lazy[rt]==-1) return;
    int mid=(l+r)>>1;
    if (lazy[rt]==1)
    {
        f[rt<<1].len=f[rt<<1|1].len=0;
        f[rt<<1].left=f[rt<<1|1].left=0;
        f[rt<<1].right=f[rt<<1|1].right=0;
        lazy[rt<<1]=lazy[rt<<1|1]=1;
    }
    if (lazy[rt]==0)
    {
        f[rt<<1].len=f[rt<<1].left=f[rt<<1].right=mid-l+1;
        f[rt<<1|1].len=f[rt<<1|1].left=f[rt<<1|1].right=r-mid;
        lazy[rt<<1]=lazy[rt<<1|1]=0;
    }
    lazy[rt]=-1;
}
void update(int rt,int l, int r,int x,int y,int op)
{
    if (x<=l && r<=y)
    {
        if (op==1)
        {
            f[rt].len=f[rt].left=f[rt].right=0;
            lazy[rt]=1;
        }
        else if (op==2)
        {
            f[rt].len=f[rt].left=f[rt].right=r-l+1;
            lazy[rt]=0;
        }
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if (x<=mid) update(rt<<1,l,mid,x,y,op);
    if (y>mid) update(rt<<1|1,mid+1,r,x,y,op);
    pushup(rt,l,r);
}
int query(int rt,int l,int r,int x)
{
    if (f[rt].len<x) return 0;
    pushdown(rt,l,r);
    if (l==r) return l;
    int mid=(l+r)>>1;
    if (f[rt<<1].len>=x) return query(rt<<1,l,mid,x);
    if (f[rt<<1].right+f[rt<<1|1].left>=x) return mid-f[rt<<1].right+1;
    return query(rt<<1|1,mid+1,r,x);
}
int main()
{
    n=read();
    m=read();
    build(1,1,n);
    for (int i=0;i<m;i++)
    {
        int sign,x,d;
        sign=read();
        if (sign==1)
        {
            x=read();
            if (f[1].len>=x)
            {
                int p=query(1,1,n,x);
                printf("%d\n",p);
                if (p) update(1,1,n,p,p+x-1,1);
            }
            else printf("0\n");
        }
        else
        {
            x=read();d=read();
            update(1,1,n,x,x+d-1,2);
        }
    }
    system("pause");
    return 0;
}