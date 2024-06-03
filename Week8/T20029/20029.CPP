#include<iostream>
#include<cstdio>

using namespace std;
int f[3200000][2]={0},p[3200000]={0};
int tot=1;
void insert(int x,int index)
{
    int k=1;
    for (int i=31;i>=0;i--)
    {
        int s=(x>>i)&1;
        if (!f[k][s]) f[k][s]=++tot;
        k=f[k][s];
        p[k]=index;
    }
}
int find(int x)
{
    int k=1;
    for (int i=31;i>=0;i--)
    {
        int s=(x>>i)&1;
        if (f[k][s^1]) k=f[k][s^1]; 
        else if (f[k][s]) k=f[k][s];
        else break;
    }
    return p[k];
}
int main()
{
    int n,m;
    cin>>n>>m;
    int a[n+1];
    for (int i=1;i<=n;i++) 
    {
        cin>>a[i];
        insert(a[i],i);
    }
    for (int i=0;i<m;i++)
    {
        int x;
        cin>>x;
        printf("%d\n",a[find(x)]^x);
    }
    system("pause");
    return 0;
}