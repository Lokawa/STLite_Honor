#include<iostream>
#include<cstdio>

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
    int n,*a;
    cin>>n;
    a=new int [n];
    for (int i=0;i<n;i++) a[i]=read();
    int sum=0,top=0,s[n+1]={0};
    for (int i=0;i<n;i++)
    {
        while (top>0 && a[i]<=a[s[top]]) 
        {
            if (a[i]<a[s[top]]) sum++;
            top--;
        }
        s[++top]=i;
    }
    sum+=top;
    cout<<sum<<endl;
    system("pause");
    return 0;
}