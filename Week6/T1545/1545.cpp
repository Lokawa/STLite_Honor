#include<iostream>
#include<cstdio>

using namespace std;

const int N=6005;
int a[N][N]={0};
int n,m;
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

void add(int x,int y,int v)
{
    for (int i=x;i<=2*n;i+=i& -i)
        for (int j=y;j<=2*m;j+=j &-j)
            a[i][j]+=v;
}

long long ask(int x,int y)
{
    long long sum=0;
    for (int i=x;i>0;i-=i & -i)
        for (int j=y;j>0;j-=j & -j)
            sum+=a[i][j];
    return sum;
}

int main()
{
    m=read();
    n=read();
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        { 
           int p;
           p=read();
           add(i+j,j+n-i,p);
        }
    char op=getchar();
    while (op!=EOF)
    {
        int x,y,z;
        x=read();
        y=read();
        z=read();
        if (op=='1') add(x+y,x+n-y,z);
        else
        {
            long long ans=ask(x+z+y,x+n+z-y)-ask(x+z+y,x+n-z-y-1)-ask(x-z+y-1,x+z+n-y)+ask(x+y-z-1,x+n-z-y-1);
            printf("%lld\n",ans);
        }
        op=getchar();
    }
    system("pause");
    return 0;
}