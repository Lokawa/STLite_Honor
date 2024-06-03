#include<iostream>
#include<cstdio>

using namespace std;

struct Node
{
    Node *pre,*next;
    int num,ra;
    Node()
    {
        pre=nullptr;
        next=nullptr;
        num=0;
        ra=0;
    }
    Node(int a,int b)
    {   
        ra=b;
        num=a;
        pre=nullptr;
        next=nullptr;
    }
};
class stack
{
public:
    Node *tail,*head;
    int len;
    stack()
    {
        head=new Node;
        tail=new Node;
        head->pre=nullptr;
        tail->next=nullptr;
        head->next=tail;
        tail->pre=head;
        len=0;
    }
    ~stack()
    {
        len=0;
        while (head->next!=nullptr)
        {

            head=head->next;
            delete head->pre;
        }
        delete tail;
    }
    Node back()
    {
        return *(tail->pre);
    }
    void push(Node obj)
    {
        Node *p;
        p=new Node(obj);
        tail->pre->next=p;
        p->pre=tail->pre;
        tail->pre=p;
        p->next=tail;
        len++;
    }
    void pop()
    {
        len--;
        Node *p=tail->pre;
        tail->pre=p->pre;
        p->pre->next=tail;
        delete p;
    }
    bool empty()
    {
        if (len==0) return 1; else return 0;
    }
};
int main()
{
    int n;
    cin>>n;
    stack a;
    long long k=0,sum=0;
    a.push(Node(n,0));
    while (!a.empty())
    {
        Node cur=a.back();
        a.pop();
        if (cur.ra==0)
        {
            if (cur.num==1) sum=1;
            else
            {
                a.push(Node(cur.num,1));
                a.push(Node(cur.num-1,0));
            } 
        }
        else
        {
            long long tmp=k;
            k=sum;
            sum=sum+tmp;
        }
    }
    cout<<sum<<endl;
    system("pause");
    return 0;
}