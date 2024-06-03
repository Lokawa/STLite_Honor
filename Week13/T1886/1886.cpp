#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;
int s,n;
const int M=1e4+5;
int timee[M];
struct homework
{
    int grade,ddl;
};
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
homework a[M];
void sort(int l,int r)
{
    if (l>=r) return;
    homework mid=a[(l+r)>>1];
    int i=l,j=r;
    while (i<=j)
    {
        while (a[i].grade>mid.grade || a[i].grade==mid.grade && a[i].ddl>mid.ddl) i++;
        while (a[j].grade<mid.grade || a[j].grade==mid.grade && a[j].ddl<mid.ddl) j--;
        if (i<=j)
        {
            homework t;
            t=a[i];a[i]=a[j];a[j]=t;
            i++;j--;
        }
    }
    if (i<r) sort(i,r);
    if (j>l) sort(l,j);
}
int main()
{
    s=read();
    for (int i=0;i<s;i++)
    {
        n=read();
        int latest=0;
        for (int j=0;j<n;j++) 
        {
            a[j].grade=read();
            a[j].ddl=read();
            latest=max(latest,a[j].ddl);
        }
        long long sum=0,tot=0;
        sort(0,n-1);
        memset(timee,0,sizeof(timee));
        for (int j=0;j<n;j++)
        {
            for (int k=a[j].ddl;k>=1;k--)
            {
                if (timee[k]==0)
                {
                    timee[k]=1;
                    sum+=a[j].grade;
                    tot++;
                    break;
                }
            }
            if (tot==latest) break;
        }
        printf("%lld\n",sum);
    }
    system("pause");
    return 0;
}
    