#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

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
    int n,m;
    cin>>n>>m;
    int a[n+1]={0},sum[n+1]={0},zero[n+1]={0},up[n+1]={0};
    int f[n+1][20]={0};
    sum[0]=0;
    zero[0]=0;
    for (int i=1;i<=n;i++) 
    {
        a[i]=read();
        sum[i]=sum[i-1]+a[i];
        zero[i]=i-sum[i];
        f[i][0]=1;
    }
    int log[n+1]={0};
    log[0]=-1;
    log[1]=0;
    up[0]=0;
    up[1]=0;
    for (int i=2;i<=n;i++)
    {
        log[i]=log[i>>1]+1;
        up[i]=up[i-1];
        if (a[i]>a[i-1]) up[i]++;
    }
    for (int j=1;j<=log[n];j++)
    {
        for (int i=1;i+(1<<j)-1<=n;i++)
        {
            f[i][j]=max(f[i][j-1]+sum[i+(1<<j)-1]-sum[i+(1<<(j-1))-1],f[i+(1<<(j-1))][j-1]+zero[i+(1<<(j-1))-1]-zero[i-1]);
        }
    }
    for (int i=0;i<m;i++)
    {
        int t,l,r;
        t=read();
        l=read();
        r=read();
        if (t==2)
        {
            if (up[r]>up[l]) printf("%d\n",2); else printf("%d\n",1);
        }
        else
        {
            int x=log[r-l+1];
            printf("%d\n",max(f[l][x]+sum[r]-sum[l+(1<<x)-1],f[r+1-(1<<x)][x]+zero[r-(1<<x)]-zero[l-1]));
        }
    }
    system("pause");
    return 0;
}