#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;
const int N=500005;
int a[N]={0};
int f[N][20]={0};
int gcd(int a,int b)
{
    int x=a%b;
    while (x)
    {
        a=b;
        b=x;
        x=a%b;
    }
    return b;
}

int main()
{
    int n,m;
    cin>>n>>m;
    for (int i=1;i<=n;i++) 
    {
        cin>>a[i];
        f[i][0]=a[i];
    }
    int log[n+1]={0};
    log[0]=-1;
    log[1]=0;
    for (int i=2;i<=n;i++) log[i]=log[i>>1]+1;
    for (int j=1;j<=log[n];j++)
        for (int i=1;i+(1<<j)-1<=n;i++)
        {
            f[i][j]=gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
        }
    for (int i=0;i<m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int x=log[r-l+1];
        int p=gcd(f[l][x],f[r+1-(1<<x)][x]);
        int mid;
        int rmin,rmax,l1=l,r1=n;
        while(l1<=r1)
        {
            mid=(l1+r1)>>1;
            x=log[mid-l+1];
            if (gcd(f[l][x],f[mid-(1<<x)+1][x])>=p) l1=mid+1; else r1=mid-1;
        }
        rmax=l1-1;
        r1=n;l1=l;
        while(l1<=r1)
        {
            mid=(l1+r1)>>1;
            x=log[mid-l+1];
            if (gcd(f[l][x],f[mid-(1<<x)+1][x])<=p) r1=mid-1; else l1=mid+1;
        }
        rmin=r1+1;
        printf("%d %d\n",p,rmax-rmin);
    }
    system("pause");
    return 0;
}