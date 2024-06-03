#include<iostream>
#include<cmath>
#include<cstdio>

inline int read() {                 // read in a int and return
    char ch = getchar(); 
    int x = 0, f = 1;
    while(ch < '0' || ch > '9') 
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9') 
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    } 
    return x * f;
}

struct node
{
    int m;
    int index;
    node()
    {
        m=0;index=0;
    }
};


const int N=1e5+5;
int lg[N]={0};
node f[N+5][20];
int n,q;

int query(int l,int r)
{
    if (l==r) return 1;
    if (l>r) return 0;
    int x=lg[r-l+1],sum=0,p=0;;
    if (f[l][x].m>f[r+1-(1<<x)][x].m)
    {
        sum=f[l][x].m;
        p=f[l][x].index;
    }   
    else
    {
        sum=f[r+1-(1<<x)][x].m;
        p=f[r+1-(1<<x)][x].index;
    }
    if (sum<=p-l+1) return sum;
    else
    {
        int lm,rm;
        lm=p-l+1;
        rm=query(p+1,r);
        if (lm>rm) return lm; else return rm;
    }
}

int main()
{
    int t;
    t=read();
    lg[0]=-1;
    lg[1]=0;
    for (int i=2;i<=N;i++) lg[i]=lg[i>>1]+1;
    while (t>0)
    {
        n=read();
        q=read();
        int x=read();
        f[1][0].m=1;
        f[1][0].index=1;
        for (int i=2;i<=n;i++)
        {
            int p=read();
            if (x==p) f[i][0].m=f[i-1][0].m+1; else f[i][0].m=1;
            x=p;
            f[i][0].index=i;
        }
        for (int j=1;j<=lg[n];j++)
            for (int i=1;i+(1<<j)-1<=n;i++)
                if (f[i][j-1].m>f[i+(1<<(j-1))][j-1].m)
                {
                    f[i][j]=f[i][j-1];
                }
                else
                {
                    f[i][j]=f[i+(1<<(j-1))][j-1];
                }
        while (q>0)
        {
            int l,r;
            l=read();
            r=read();
            int ans=query(l,r);
            printf("%d\n",ans);
            q--;
        }
        t--;
    }
    system("pause");
    return 0;
}