#include<iostream>
#include<cstdio>

using namespace std;
struct point
{
    int head;
    int tail;
};

int main()
{
    int n,*cost;
    long long *f;
    cin>>n;
    cost=new int [n+1];
    f=new long long [n+1];
    f[0]=0;
    for (int i=1;i<=n;i++)
    {
        cin>>cost[i];
        f[i]=f[i-1]+cost[i];
    }
    point a[n+1];
    int s[n+1]={0},top=0;
    a[1].head=0;
    a[n].tail=n+1;
    s[0]=0;
    for (int i=1;i<=n;i++)
    {
        while (top && cost[s[top]]>=cost[i]) --top;
        a[i].head=s[top];
        s[++top]=i;
    }
    for (int i=0;i<=n;i++) s[i]=0;
    top=0;
    s[0]=n+1;
    for (int i=n;i>=1;i--)
    {
        while (top && cost[s[top]]>=cost[i]) top--;
        a[i].tail=s[top];
        s[++top]=i;
    }
    long long max=0;
    for (int i=1;i<=n;i++)
    {
        if ((f[a[i].tail-1]-f[a[i].head])*cost[i]>max)  max=cost[i]*(f[a[i].tail-1]-f[a[i].head]);
    }
    cout<<max<<endl;
    system("pause");
    return 0;
}