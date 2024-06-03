#include<iostream>
#include<cstdio>

const int N=2.5e5+7;
int f[N],h[N],du[N],n;
bool a[N]={0};
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

int find(int x)
{
    if (f[x]==x) return x;
    return f[x]=find(f[x]);
}

void unit(int x,int y)
{
    x=find(x);
    y=find(y);
    if (x==y) return;
    if (h[x]<h[y]) 
    {
        f[x]=y;
    }
    else if (h[x]>h[y])
    {
        f[y]=x;
    }
    else
    {
        f[x]=y;
        h[y]++;
    }
}

int main()
{
    n=read();
    for (int i=0;i<N;i++) f[i]=i;
    int m=0;
    for (int i=0;i<n;i++)
    {
        int x,y;
        x=read();
        y=read();
        if (x!=y)
        {
            unit(x,y);
            du[x]++;
            du[y]++;
        }
        a[x]=1;
        a[y]=1;
        m=std::max(std::max(x,y),m);
    }
    int t=find(m),tot=0;
    bool flag=true;
    for (int i=0;i<m;i++)
    {
        if (a[i])
        {
            if (du[i]%2==1) tot++;
            if (find(i)!=t)
            {
                flag=false;
                break;
            }
        }
    }
    if (!flag)
    {
        printf("Impossible\n");
    }
    else if (tot==0 || tot==2) printf("Possible\n");
    else printf("Impossible\n");
    system("pause");
    return 0;
}