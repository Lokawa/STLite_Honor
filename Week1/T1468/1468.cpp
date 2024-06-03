#include<iostream>
#include<cstdio>
using namespace std;
template <typename T>
struct Node
    {
        Node *next,*pre;
        T data;
        Node(const T &x, Node *p=NULL, Node *q=NULL)
        {
            data=x;
            pre=p;
            next=q;
        }
        Node():next(NULL),pre(NULL){}
        ~Node(){}
    };

template <typename T>
class LinkedList
{   
public:
    int n;
    Node<T> *head,*tail;
    LinkedList()
    {
        head=new Node<T>;
        tail=new Node<T>;
        head->next=tail;
        head->pre=nullptr;
        tail->pre=head;
        tail->next=nullptr;
        n=0;
    }
    LinkedList(const LinkedList &a)
    {
        Node<T> *p;
        head=new Node<T>;
        tail=new Node<T>;
        head->pre=nullptr;
        tail->next=nullptr;
        head->next=tail;
        tail->pre=head;
        n=a.n;
        p=a.head;
        while (p)
        {
            p=p->next;
            tail->data=p->data;
            Node<T> *q=new Node<T>;
            q->pre=tail;
            tail->next=q;
            tail=q;
        }
        tail->next=nullptr;
    }
    int size()
    {
        return n;
    }
    void print()
    {
        Node<T> *p=head->next;
        while (p!=tail)
        {
            std::cout<<p->data;
            p=p->next;
            if (p!=tail) cout<<' ';
        }
        cout<<endl;
    }
    ~LinkedList()
    {
        Node<T>*p=head->next,*q;
        while (p!=tail)
	    {
		    q=p->next;
		    delete p;
            p=q;
	    }
	    delete head;
        delete tail;
        n=0;
    }
    void pushFront(T x)
    {
        Node<T> *p=new Node<T>;
        p->data=x;
        p->next=head->next;
        p->pre=head;
        head->next->pre=p;
        head->next=p;
        n++;
    }
    void pushBack(T x)
    {
        Node<T> *p=new Node<T>;
        p->next=tail;
        p->pre=tail->pre;
        p->data=x;
        tail->pre->next=p;
        tail->pre=p;
        n++;
    }
    T popFront()
    {
        Node<T> *p;
        T val=head->next->data;
        p=head->next;
        head->next=p->next;
        p->next->pre=head;
        delete p;
        n--;
        return val;
    }
    T popBack()
    {
        Node<T> *p;
        T val=tail->pre->data;
        p=tail->pre;
        tail->pre=p->pre;
        p->pre->next=tail;
        delete p;
        n--;
        return val;
    }
    virtual T peak(){return head->next->data;}
    virtual T pop(){return tail->pre->data;}
    virtual const char* name(){return "LinkedList";}
    virtual void push(T val){}
};

template <typename T>
class Stack:public LinkedList<T>
{
public:
    const char* name()
    {
        return "Stack";
    }
    T peak()
    {
        return this->tail->pre->data;
    }
    T pop()
    {
        T val=this->tail->pre->data;
        Node<T> *p=this->tail->pre;
        this->tail->pre=p->pre;
        p->pre->next=this->tail;
        this->n--;
        delete p;
        return val;
    }
    void push(T val)
    {
        Node<T> *p=new Node<T>;
        p->next=this->tail;
        p->pre=this->tail->pre;
        p->data=val;
        this->tail->pre->next=p;
        this->tail->pre=p;
        this->n++;
    }
};

template <typename T>
class Queue:public LinkedList<T>
{
public:
    const char* name()
    {
        return "Queue";
    }
    T peak()
    {
        return this->head->next->data;
    }
    T pop()
    {
        T val=this->head->next->data;
        Node<T> *p;
        p=this->head->next;
        this->head->next=p->next;
        p->next->pre=this->head;
        this->n--;
        delete p;
        return val;
    }
    void push(T val)
    {
        Node<T> *p=new Node<T>;
        p->next=this->tail;
        p->pre=this->tail->pre;
        p->data=val;
        this->tail->pre->next=p;
        this->tail->pre=p;
        this->n++;
    }
};

int main() {
    LinkedList<int> * list = new LinkedList<int>;
    LinkedList<int> * stack = new Stack<int>;
    LinkedList<int> * queue = new Queue<int>;

    cout << "LinkedList" << endl;
    list->pushFront(1);
    list->pushBack(2);
    list->pushBack(3);
    list->pushFront(4);
    list->print();
    list->popFront();
    list->popBack();
    list->print();
    cout << list->size() << endl;

    cout << stack->name() << endl;
    stack->push(1);
    stack->push(2);
    stack->push(3);
    stack->push(4);
    cout << stack->peak() << endl;
    stack->pop();
    cout << stack->pop() << endl;
    cout << stack->peak() << endl;

    cout << queue->name() << endl;
    queue->push(1);
    queue->push(2);
    queue->push(3);
    queue->push(4);
    cout << queue->peak() << endl;
    queue->pop();
    cout << queue->pop() << endl;
    cout << queue->peak() << endl;

    delete list;
    delete stack;
    delete queue;
    system("pause");
    return 0;
}