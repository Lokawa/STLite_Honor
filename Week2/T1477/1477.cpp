#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;
void print(int x,int *next)
{
    if (x>0 && next[x]>0) print(next[x],next);
    cout<<x+1<<endl;
    return;
}
int main()
{
    char target[1000000];
    cin>>target;
    int len=strlen(target),*next;
    next=new int [len+1];
    next[0]=-1;
    int k=-1,i=0;
    while (i<len)
    {
        if (k==-1|| target[i]==target[k])
        {
            k++;i++;
            next[i]=k;
        }
        else k=next[k];
    }
    if (target[0]==target[len-1]) cout<<1<<endl;
    print(len-1,next);
    system("pause");
    return 0;
}
