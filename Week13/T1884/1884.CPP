#include<iostream>
#include<cstdio>
#include<cstring>

const int M=2e6+7;
const int mod=1e6+7;
int fa[mod],h[mod],f[mod];
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
struct notequal
{
    int x,y;
};
notequal a[M>>1];
int query(int x)
{
    if (fa[x]==x) return x;
    return fa[x]=query(fa[x]);
}
void unit(int x,int y)
{
    x=query(x);
    y=query(y);
    if (x==y) return;
    if (h[x]<h[y]) 
    {
        fa[x]=y;
    }
    else if (h[x]>h[y])
    {
        fa[y]=x;
    }
    else
    {
        fa[x]=y;
        h[y]++;
    }
}
int hash()
{
    int x = 0;
    long long p=0;
    char ch = getchar();
    while (ch < '0' || ch > '9'){ch = getchar();}
    while (ch >= '0' && ch <= '9')
    {
        x = (x<<3) +(x>>1)+ch - '0';
        p=(p<<4)+p+ch-'0'; 
        ch = getchar();
    }
    p=p%mod;
    int i=1;
    while (f[p]!=0 && f[p]!=x)
    {
        p=(p+(i<<1)+1)%mod;
        i++;
    }
    f[p]=x;
    return p;
}
int main()
{
    int t,n;
    t=read();
    for (int i=0;i<t;i++)
    {
        std::memset(fa,0,sizeof(fa));
        std::memset(h,0,sizeof(h));
        std::memset(f,0,sizeof(f));
        n=read();
        int tot=0;
        int x,y,sign;
        for (int j=0;j<n;j++)
        {
            x=hash();
            y=hash();
            sign=read();
            if (!fa[x]) fa[x]=x;
            if (!fa[y]) fa[y]=y;
            if (sign==1) unit(x,y);
            else
            {
                a[tot].x=x;
                a[tot].y=y;
                tot++;
            }
        }
        int j;
        for (j=0;j<tot;j++)
        {
            x=query(a[j].x);y=query(a[j].y);
            if (x==y)
            {
                printf("NO\n");
                break;
            }
        }

        if (j==tot) printf("YES\n");
    }
    system("pause");
    return 0;
}