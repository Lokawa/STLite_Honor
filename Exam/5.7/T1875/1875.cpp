#include<iostream>
#include<cstdio>

int n,lazy[5200000],tree[5200000];
struct platform
{
    int left,right,height,value;
};
platform a[5200000];
void build(int rt,int l, int r)
{
    if (l<=a[0].left && a[0].left<=r || l<=a[0].right && a[0].right<=r) tree[rt]=100+a[0].value;
    else tree[rt]=-1;
    if (l==r) return;
    int mid=(l+r)>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
void update(int rt,int l,int r,int x,int y,int v)
{
    if (x<l && r<y) 
    {
        tree[rt]=-1;
        lazy[rt]=1;
        return;
    }
    else if (l==r) 
    {
        tree[rt]=v;
        return;
    }
    int mid=(l+r)>>1;
    if (lazy[rt]==1)
    {
        lazy[rt]=0;
        lazy[rt<<1]=lazy[rt<<1|1]=1;
        tree[rt<<1]=tree[rt<<1|1]=-1;
    }
    if (x<=mid) update(rt<<1,l,mid,x,y,v);
    if (y>mid) update(rt<<1|1,mid+1,r,x,y,v);
    tree[rt]=std::max(tree[rt<<1],tree[rt<<1|1]);
}
int query(int rt,int l,int r,int x,int y)
{
    if (x<=l && r<=y)
    {
        return tree[rt];
    }
    if (lazy[rt]==1) return -1;
    int mid=(l+r)>>1;
    if (y<=mid) return query(rt<<1,l,mid,x,y);
    if (x>mid) return query(rt<<1|1,mid+1,r,x,y);
    return std::max(query(rt<<1,l,mid,x,y),query(rt<<1|1,mid+1,r,x,y)); 
}
void sort(int l,int r)
{
    if (l>=r) return;
    int i=l,j=r;
    platform t=a[l];
    while (i<j)
    {
        while (a[i].height>=t.height && i<j) i++;
        while (a[j].height<=t.height && i<j) j--;
        if (i<j)
        {
            platform tmp;
            tmp=a[i];a[i]=a[j];a[j]=tmp;
        }
    }   
    a[l]=a[i];
    a[i]=t;
    sort(l,i-1);
    sort(i+1,r);
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++)   
    {
        scanf("%d %d %d %d",&a[i].height,&a[i].left,&a[i].right,&a[i].value);
    }
    sort(0,n-1);
    if (a[0].value<=-100)
    {
        printf("-1\n");
        return 0;
    }
    build(1,1,1000000);
    for (int i=1;i<n;i++)
    {
        int p=query(1,1,1000000,a[i].left,a[i].right);
        if (p<0) continue;
        if (p+a[i].value<=0) update(1,1,1000000,a[i].left,a[i].right,-1);
        else update(1,1,1000000,a[i].left,a[i].right,a[i].value+p);
    }
    printf("%d\n",tree[1]);
    system("pause");
    return 0;
}