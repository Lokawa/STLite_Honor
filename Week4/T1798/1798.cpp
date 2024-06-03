#include<iostream>
#include<cstdio>

using namespace std;

inline int read() 
{
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
    int n,m,*a;
    cin>>n>>m;
    a=new int [n];
    a[0]=read();
    int max=a[0];
    for (int i=1;i<n;i++)
    {
        int x;
        x=read();
        a[i]=x+a[i-1];
        if (i<m) 
        {
            if (a[i]>max) max=a[i];
        } 
        else 
        {
            if (a[i]-a[i-m]>max) max=a[i]-a[i-m];
        }
    }
    int head=1,tail=0,s[n+1]={0};
    for (int i=0;i<n;i++)
    {
        while (head<=tail && a[s[tail]]>=a[i]) tail--;
        s[++tail]=i;
        while (s[head]<=i-m) ++head;
        if (a[i]-a[s[head]]>=max) max=-a[s[head]]+a[i];
    }
    cout<<max<<endl;
    system("pause");
    return 0;
}