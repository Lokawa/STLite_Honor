#include<iostream>
#include<cstdio>

using namespace std;

struct tree
{
    int h;
    int x;
};
 
void kp(tree *a,int l,int r)
{
    tree mid=a[(l+r)/2];
    int i=l,j=r;
    while (i<=j)
    {
        while (a[i].x<mid.x) i++;
        while (a[j].x>mid.x) j--;
        if (i<=j)
        {
            tree tmp;
            tmp=a[i];a[i]=a[j]; a[j]=tmp;
            i++;j--;
        }
    }
    if (i<r) kp(a,i,r);
    if (j>l) kp(a,l,j);
};
int main()
{
    int n,d;
    cin>>n>>d;
    tree *a;
    a=new tree[n];
    for (int i=0;i<n;i++)
    {
        cin>>a[i].x>>a[i].h;
    }
    kp(a,0,n-1);
    int f[n+1]={0},s[n+1]={0};
    int head=1,tail=0;
    for (int i=0;i<=n;i++)
    {
        while (head<=tail && a[s[tail]].h<=a[i].h) tail--;
        s[++tail]=i;
        while (a[s[head]].x<a[i].x-d) ++head;
        if (a[s[head]].h>=2*a[i].h) f[i]++;
    }
    for (int i=0;i<n;i++) s[i]=0;
    head=1;
    tail=0;
    for (int i=n-1;i>=0;i--)
    {
        while (head<=tail && a[s[tail]].h<=a[i].h) tail--;
        s[++tail]=i;
        while (a[s[head]].x-a[i].x>d) ++head;
        if (a[s[head]].h>=2*a[i].h) f[i]++;
    }
    int sum=0;
    for (int i=0;i<n;i++) if (f[i]==2) sum++;
    cout<<sum<<endl;
    for (int i=0;i<n;i++) if (f[i]==2) cout<<a[i].x<<' ';
    cout<<endl;
    system("pause");
    return 0;
}