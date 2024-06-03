#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>

using namespace std;


int main()
{
    char target[1000000],source[1000000];
    int k=-1,i=0;
    cin>>source;
    cin>>target;
    int *next;
    next=new int [strlen(target)];
    next[0]=-1;
    while (i<strlen(target))
    {
        if (k==-1 || target[i]==target[k]) 
        {
            i++;k++;
            next[i]=k;
        }
        else 
        {
            k=next[k];
        }
    }
    int TargetCursor=0,SourceCursor=0;
    while (SourceCursor<strlen(source))
    {
        if (TargetCursor==-1 || target[TargetCursor]==source[SourceCursor])
        {
            TargetCursor++;
            SourceCursor++;
            if (TargetCursor==strlen(target)) 
            {
                cout<<SourceCursor-strlen(target)+1<<endl;
                TargetCursor=next[TargetCursor];
            }
        }
        else 
        {
            TargetCursor=next[TargetCursor];
        }
    }
    for (i=1;i<strlen(target);i++) cout<<next[i]<<' ';
    cout<<next[strlen(target)]<<endl;
    system("pause");
    return 0;
}