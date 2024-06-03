#include<iostream>
#include<cstdio>
using namespace std;

const int nmax=100005;
int n,m;

struct hafu
{
    int data,parent=0;
    int h=0;
};

struct node
{
    int index, data;
    node():index(0),data(0){}
    node(const node &x)
    {
        index=x.index;
        data=x.data;
    }
};

hafu f[200000];
node a[nmax];

node pop()
{
    node r=a[1];
    a[1]=a[n--];
    node tmp=a[1];
    int child, now=1;
    for(;(now<<1)<=n;now=child)
    {
        child=now*2;
        if(child!=n && a[child+1].data<a[child].data) child++;
        if(a[child].data<tmp.data) a[now]=a[child];
        else break;
    }
    a[now]=tmp;
    return r;
}

void push(int value, int index)
{
    node x;
    x.data=value;
    x.index=index;
    int now=++n;
    while(now>1 && a[now>>1].data>x.data)
    {
        a[now]=a[now>>1];
        now/=2;
    }
    a[now]=x;
}

inline int read() {                 // read in a int and return
    char ch = getchar();
    int x = 0, f = 1;
    while(ch < '0' || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() 
{
    n=read();
    m=read();
    for (int i=1;i<=n;i++) cin>>a[i].data;
    if (n==1) 
    {
        cout<<a[1].data;
        return 0;
    }
    for (int i=n>>1;i>0;i--) 
    {
        node tmp=a[i];
        int child,now=i;
        for (; (now<<1)<=n; now=child) 
        {
            child=now * 2;
            if (child!= n && a[child+1].data<a[child].data) child++;
            if (a[child].data<tmp.data) a[now] = a[child];
            else break;
        }
        a[now]=tmp;
    }
    int zero=(n-1)%(m-1);
    if (zero>0) zero=m-1-zero;
    int e=(n+zero-1)/(m-1), k=e, size=(n+k), len=(size+zero), l=zero;
    for (int i=0;i<zero;i++) 
    {
        f[len].data=0;
        f[len--].parent=k;
    }
    while (n>1) 
    {
        int sum=0;
        while (l<m) 
        {
            node pp=pop();
            if (pp.index==0) 
            {
                f[len].data=pp.data;
                f[len--].parent=k;
            } else 
            {
                f[pp.index].parent=k;
            }
            l++;
            sum+=pp.data;
        }
        push(sum,k);
        f[k].data=sum;
        l=0;
        k--;
    }
    long long ans=0;
    for (int i=2;i<=e;i++) f[i].h=f[f[i].parent].h+1;
    for (int i=e+1;i<=size;i++) 
    {
        f[i].h=f[f[i].parent].h+1;
        ans+=f[i].h*f[i].data;
    }
    cout<<ans<<endl;
    system("pause");
    return 0;
}
