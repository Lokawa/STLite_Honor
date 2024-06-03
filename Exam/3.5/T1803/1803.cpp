#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int main()
{
    int n;
    cin>>n;
    long long *next;
    for (int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        long long sum=0;
        long long position=0,last=-1;
        long long len=s.size();
        next=new long long [len+1];
        memset(next,0,sizeof(long long)*(len+1));
        next[0]=-1;
        while(position<len)
        {
            if (last==-1 ||s[position]==s[last])
            {
                position++;
                last++;
                next[position]=last;
            }
            else last=next[last];
        }
        for (position=1;position<=len;position++)
        {
            last=next[position];
            while (next[last]>0) last=next[last];
            next[position]=last;
            if (next[position]!=0) sum+=position-next[position];
        }
        cout<<sum<<endl;
        delete []next;
    }
    system("pause");
    return 0;
}
