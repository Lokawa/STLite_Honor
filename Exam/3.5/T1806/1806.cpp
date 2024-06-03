#include <iostream>
#include <cstring>
#include <string>
#include<cstdio>

using namespace std;
struct shell
{
    string str;
    shell *next;
    shell *pre;
};
int main()
{
    int n;
    cin>>n;
    shell *head,*tail,*f;
    head=new shell;
    tail=new shell;
    f=new shell;
    f->str="/";
    f->pre=head;
    f->next=tail;
    head->pre=nullptr;
    head->next=f;
    tail->pre=f;
    tail->next=nullptr;
    char s[1000];
    for (int i=0;i<n;i++)
    {
        cin>>s;
        string ss;
        bool flag=true;
        for (int j=0;j<strlen(s);j++)
        {
            if (s[j]=='/')
            {
                if (j==0)
                {
                    shell *pp=f->next;
                    while (pp!=tail)
                    {
                        shell *q=pp;
                        pp=pp->next;
                        delete q;
                    }
                    head->next=f;
                    f->pre=head;
                    f->next=tail;
                    tail->pre=f;
                }
                else if (flag)
                {
                    ss+=s[j];
                    shell *p;
                    p=new shell;
                    p->str=ss;
                    p->next=tail;
                    p->pre=tail->pre;
                    tail->pre->next=p;
                    tail->pre=p;
                    ss.clear();
                }
                flag=true;
            }
            if (s[j]!='.' && s[j]!='/')
            {
                ss+=s[j];
                flag=true;
            }
            if (s[j]=='.' && flag)
            {
                flag=false;
                continue;
            }
            if (s[j]=='.' && !flag)
            {
                shell *p=tail->pre;
                if (p!=f)
                {
                    tail->pre=p->pre;
                    p->pre->next=tail;
                    delete p;
                }
            }
        }
        ss.clear();
        shell *q=head->next;
        while (q!=tail)
        {
            cout<<q->str;
            q=q->next;
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}