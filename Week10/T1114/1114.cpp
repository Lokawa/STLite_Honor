#include<iostream>
#include<cstdio>
#include<cstring>

const int N=1e5+5;
int n,m,tree[N<<2][26],lazy[N<<2],sum[26];
char str[N];

void pushup(int rt)
{
    for (int i=0;i<26;i++) 
        tree[rt][i]=tree[rt<<1][i]+tree[rt<<1|1][i];
}
void build(int rt,int l,int r)
{
    lazy[rt]=0;
    if (l==r)
    {
        tree[rt][str[l]-'a']=1;
        return;
    }
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void pushdown(int rt,int l,int r)
{
    if(!lazy[rt]) return;
    for (int i=0;i<26;i++) 
        tree[rt<<1][i]=tree[rt<<1|1][i]=0;
    int mid=(l+r)>>1,len1=mid-l+1,len2=r-mid;
    if (lazy[rt]==1)
    {
        for (int i=0;i<26&&len1;i++)
        {
            if (len1<tree[rt][i])
            {
                tree[rt<<1][i]+=len1;
                len1=0;
                break;
            }
            else
            {
                tree[rt<<1][i]+=tree[rt][i];
                len1-=tree[rt][i];
            }
        }
        for (int i=25;i>=0 && len2;i--)
        {
            if (len2<tree[rt][i])
            {
                tree[rt<<1|1][i]+=len2;
                len2=0;
                break;
            }
            else
            {
                tree[rt<<1|1][i]+=tree[rt][i];
                len2-=tree[rt][i];
            }
        }
        lazy[rt<<1]=lazy[rt<<1|1]=1;
    }
    else if (lazy[rt]==2)
    {
        for (int i=25;i>=0 && len1;i--)
        {
            if (len1<tree[rt][i])
            {
                tree[rt<<1][i]+=len1;
                len1=0;
                break;
            }
            else
            {
                tree[rt<<1][i]+=tree[rt][i];
                len1-=tree[rt][i];
            }
        }
        for (int i=0;i<26 && len2;i++)
        {
            if (len2<tree[rt][i])
            {
                tree[rt<<1|1][i]+=len2;
                len2=0;
                break;
            }
            else
            {
                tree[rt<<1|1][i]+=tree[rt][i];
                len2-=tree[rt][i];
            }
        }
        lazy[rt<<1]=lazy[rt<<1|1]=2;
    }
    lazy[rt]=0;
}
void update(int rt,int l,int r,int x,int y,int op)
{
    if (x<=l && r<=y)
    {
        lazy[rt]=op;
        for (int i=0;i<26;i++) tree[rt][i]=0;
        int len=r-l+1;
        if (op==1)
        {
            for (int i=0;i<26 && len;i++)
            {
                if (len<sum[i])
                {
                    tree[rt][i]+=len;
                    sum[i]-=len;
                    len=0;
                    break;
                }
                else 
                {
                    tree[rt][i]+=sum[i];
                    len-=sum[i];
                    sum[i]=0;
                }
            }
        }
        else 
        {
            for (int i=25;i>=0 && len;i--)
            {
                if (len<sum[i])
                {
                    tree[rt][i]+=len;
                    sum[i]-=len;
                    len=0;
                    break;
                }
                else 
                {
                    tree[rt][i]+=sum[i];
                    len-=sum[i];
                    sum[i]=0;
                }
            }
        }
        return;
    }
    int mid=(l+r)>>1;
    pushdown(rt,l,r);
    if (x<=mid) update(rt<<1,l,mid,x,y,op);
    if (y>mid) update(rt<<1|1,mid+1,r,x,y,op);
    pushup(rt);
}
void query(int rt,int l,int r,int x,int y)
{
    if (x<=l && r<=y)
    {
        for (int i=0;i<26;i++) sum[i]+=tree[rt][i];
        return;
    }
    int mid=(l+r)>>1;
    pushdown(rt,l,r);
    if (x<=mid) query(rt<<1,l,mid,x,y);
    if (y>mid) query(rt<<1|1,mid+1,r,x,y);
}
void print(int rt,int l,int r)
{
    if (l==r)
    {
        for (int i=0;i<26;i++) if (tree[rt][i]) printf("%c",i+'a');
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    print(rt<<1,l,mid);
    print(rt<<1|1,mid+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",str+1);
    build(1,1,n);
    for (int i=0;i<m;i++)
    {
        int l,r,sign;
        scanf("%d%d%d",&l,&r,&sign);
        if (sign==0) sign=2;
        std::memset(sum,0,sizeof(sum));
        query(1,1,n,l,r);
        update(1,1,n,l,r,sign);
    }
    print(1,1,n);
    system("pause");
    return 0;
}