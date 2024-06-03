#include<iostream>

using namespace std;

struct Node
{
    Node *pre,*next;
    int num;
};
int main()
{
    Node **a,*head,*tail;
    int i,n,m;
    cin>>n;
    a=new Node*[n+1];
    head=new Node;
    tail=new Node;
    a[0]=new Node;
    a[0]->pre=head;
    a[0]->next=tail;
    a[0]->num=1;
    head->pre=nullptr;
    head->next=a[0];
    tail->next=nullptr;
    tail->pre=a[0];
    for (i=1;i<n;i++)
    {
        a[i]=new Node;
        a[i]->num=i+1;
        int k,j;
        cin>>k>>j;
        k=k-1;
        if (j==0)
        {
            a[i]->pre=a[k]->pre;
            a[k]->pre->next=a[i];
            a[i]->next=a[k];
            a[k]->pre=a[i];
        }
        else
        {
            a[i]->next=a[k]->next;
            a[k]->next->pre=a[i];
            a[i]->pre=a[k];
            a[k]->next=a[i];
        }
    }
    cin>>m;
    for (i=0;i<m;i++)
    {
        int k;
        cin>>k;
        k--;
        if (a[k])
        {
            a[k]->pre->next=a[k]->next;
            a[k]->next->pre=a[k]->pre;
            delete a[k];
            a[k]=nullptr;
        }
    }
    Node *p=head->next;
    while (p!=tail)
    {
        cout<<p->num;
        Node *q=p;
        p=p->next;
        delete q;
        if (p!=tail) cout<<' ';
    }
    delete []a;
    cout<<endl;
    system("pause");
    return 0;
}