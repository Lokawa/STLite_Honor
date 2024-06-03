#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

struct dd
{
    int h,x;
};
void kp(dd *a,int l,int r)
{
    int i=l,j=r;
    dd mid=a[(l+r)/2];
    while (i<=j)
    {
        while (a[i].x<mid.x) i++;
        while (a[j].x>mid.x) j--;
        if (i<=j)
        {
            dd t;
            t=a[i];a[i]=a[j];a[j]=t;
            i++;j--;
        }
    }
    if (i<r) kp(a,i,r);
    if (l<j) kp(a,l,j);
}
int main()
{
    int n,d;
    cin>>n>>d;
    dd *a=new dd[n];
    for (int i=0;i<n;i++)
    {
        cin>>a[i].x>>a[i].h;
    }
    kp(a,0,n-1);
    int head1=1,tail1=0,s1[n+1]={0},s2[n+1]={0},head2=1,tail2=0;
    int min=100000001;
    int l=0;
    for (int i=0;i<n;i++)
    {
        while (head1<=tail1 && a[i].h<=a[s1[tail1]].h) tail1--;
        while (head2<=tail2 && a[i].h>=a[s2[tail2]].h) tail2--;
        s1[++tail1]=i;
        s2[++tail2]=i;
        while (a[s2[head2]].h-a[s1[head1]].h>=d) 
        {
            if (abs(-a[s1[head1]].x+a[s2[head2]].x)<min) 
            {
                min=abs(-a[s1[head1]].x+a[s2[head2]].x);
            }
            l++;
            while (head1<=tail1 && s1[head1]<l) head1++;
            while (head2<=tail2 && s2[head2]<l) head2++;
        }
        
    }   
    if (min==100000001) cout<<-1<<endl; else cout<<min<<endl;
    system("pause");
    return 0;
}
