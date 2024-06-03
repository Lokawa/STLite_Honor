#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int n;
const int N=100005;
int m=0;
int a[N]={0},f[N]={0}; 

void add(int x)
{
    for (int i=x;i<=m;i+=i & -i) f[i]+=1;
}
int ask(int x)
{
    int sum=0;
    for (int i=x;i>0;i-=i & -i) sum+=f[i];
    return sum;
}
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++) 
    {
        cin>>a[i];
        if (m<a[i]) m=a[i];
    }
    int l[n+1]={0},r[n+1]={0};
    for (int i=1;i<=n;i++)
    {
        add(a[i]);
        l[i]=ask(m)-ask(a[i]);
    }
    for (int i=0;i<N;i++) f[i]=0;
    for (int i=n;i>0;i--)
    {
        add(a[i]);
        r[i]=ask(m)-ask(a[i]);
    }
    int ans=0;
    for (int i=1;i<=n;i++)
        if (max(l[i],r[i])>2*min(l[i],r[i])) ans++;
    cout<<ans<<endl;
    system("pause");
    return 0;
} 