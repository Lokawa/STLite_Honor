#include<iostream>
#include<cstdio>

int a,b,c,x,y,z,roota,rootb,rootc,rootx,rooty,rootz;

inline void range(int &a,int &b,int &c)
{
    int t;
    if (a>b) std::swap(a,b);
    if (b>c) std::swap(b,c);
    if (a>c) std::swap(a,c);
}

int root(int x,int y,int z,int &roota,int &rootb,int &rootc)
{
    int d1=y-x,d2=z-y,sum=0,t;
    while (2*y!=x+z)
    {
        if (d2>d1)
        {
            t=d2/d1;
            if (d2%d1==0) t--;
            sum+=t;
            y+=t*d1;
            x+=t*d1;
            d2-=t*d1;
        }
        else if (d2<d1)
        {
            t=d1/d2;
            if (d1%d2==0) t--;
            sum+=t;
            y-=t*d2;
            z-=t*d2;
            d1-=t*d2;
        }
    }
    roota=x;
    rootb=y;
    rootc=z;
    return sum;
}
void jump(int x,int y, int z,int &rootx,int &rooty,int &rootz,int tot)
{
    int d1=y-x,d2=z-y,t;
    while (tot)
    {
        if (d2>d1)
        {
            t=d2/d1;
            if (d2%d1==0) t--;
            if (t>=tot)
            {
                x+=tot*d1;
                y+=tot*d1;
                rootx=x;
                rooty=y;
                rootz=z;
                break;
            }
            else 
            {
                y+=t*d1;
                x+=t*d1;
                d2-=t*d1;
                tot-=t;
            }
        }
        else
        {
            t=d1/d2;
            if (d1%d2==0) t--;
            if (t>=tot)
            {
                y-=tot*d2;
                z-=tot*d2;
                rootx=x;rooty=y;rootz=z;
                break;
            }
            else
            {
                y-=t*d2;
                z-=t*d2;
                d1-=t*d2;
                tot-=t;
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d%d%d",&a,&b,&c,&x,&y,&z);
    range(a,b,c);
    range(x,y,z);
    int sum1=root(a,b,c,roota,rootb,rootc),sum2=root(x,y,z,rootx,rooty,rootz);
    if (roota!=rootx || rootb!=rooty || rootc!=rootz)
    {
        printf("NO\n");
        return 0;
    }
    else
        printf("YES\n");
    int tot=0;
    if (sum1>sum2)
    {
        jump(a,b,c,roota,rootb,rootc,sum1-sum2);
        a=roota;b=rootb;c=rootc;
        tot+=sum1-sum2; sum1=sum2;
    }
    else if (sum1<sum2)
    {
        jump(x,y,z,rootx,rooty,rootz,sum2-sum1);
        x=rootx,y=rooty,z=rootz;
        tot+=sum2-sum1; sum2=sum1;
    }
    if (sum1==0) 
    {
        printf("%d\n",tot);
        return 0;
    }     
    int t=sum1;
    while(true)
    {
        t=(t+1)>>1;
        jump(a,b,c,roota,rootb,rootc,t);
        jump(x,y,z,rootx,rooty,rootz,t);
        if (roota!=rootx || rootb!=rooty || rootc!=rootz)
        {
            tot+=2*t;
            a=roota,b=rootb,c=rootc;
            x=rootx,y=rooty,z=rootz;
        }
        else if (t==1) {tot+=2;break;}
    }   
    printf("%d\n",tot);
    return 0;
}