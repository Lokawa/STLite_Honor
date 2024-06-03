#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
protected:
    class node {
    public:
        /**
         * add data members and constructors & destructor
         */
        node *pre,*next;
        T* data;
        std::allocator<T> alloc;
        node(T p)
        {
            data=alloc.allocate(1);
            alloc.construct(data,p);
            pre=nullptr;
            next=nullptr;
        }
        node(const node &p)
        {
            data=alloc.allocate(1);
            alloc.construct(data,*(p.data));
            pre=nullptr;
            next=nullptr;
        }
        node()
        {
            data=alloc.allocate(1);
            pre=nullptr;
            next=nullptr;
        }
        ~node()
        {
            if (pre != nullptr && next != nullptr) alloc.destroy(data);
            alloc.deallocate(data, 1);
        }
    };

protected:
    /**
     * add data members for linked list as protected members
     */

    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    node *insert(node *pos, node *cur) {
        pos->pre->next=cur;
        cur->pre=pos->pre;
        cur->next=pos;
        pos->pre=cur;
        len++;
        return cur;
    }
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    node *erase(node *pos) {
        pos->pre->next = pos->next;
        pos->next->pre = pos->pre;
        len--;
        return pos;
    }
    node *head,*tail;
    int len;

public:
    class const_iterator;
    class iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        node *cur;
        node *src;
    public:
        iterator &operator=(const iterator &tmp)
        {
            if (&tmp==this) return *this;
            cur=tmp.cur;
            src=tmp.src;
            return *this;
        }
        /**
         * iter++
         */
        iterator operator++(int) {
            if (cur->next== nullptr) throw invalid_iterator();
            iterator tmp=*this;
            this->cur=this->cur->next;
            return tmp;
        }
        /**
         * ++iter
         */
        iterator & operator++() {
            if (cur->next== nullptr) throw invalid_iterator();
            this->cur=this->cur->next;
            return *this;
        }
        /**
         * iter--
         */
        iterator operator--(int) {
            if (cur->pre->pre== nullptr) throw invalid_iterator();
            iterator tmp=*this;
            this->cur=this->cur->pre;
            return tmp;
        }
        /**
         * --iter
         */
        iterator & operator--() {
            if (cur->pre->pre== nullptr) throw invalid_iterator();
            this->cur=this->cur->pre;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const {
            if (cur->pre==nullptr|| cur->next== nullptr) throw invalid_iterator();
            return *(cur->data);

        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const noexcept {
            if (cur->pre==nullptr|| cur->next== nullptr) throw invalid_iterator();
            return (cur->data);
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {
            if (cur==rhs.cur) return 1; else return 0;
        }
        bool operator==(const const_iterator &rhs) const {
            if (cur==rhs.cur) return 1; else return 0;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            if (cur==rhs.cur) return 0; else return 1;
        }
        bool operator!=(const const_iterator &rhs) const {
            if (cur==rhs.cur) return 0; else return 1;
        }
        friend class const_iterator;
        friend class list;
        iterator(const iterator &t)
        {
            cur=t.cur;
            src=t.src;
        }
        iterator(const const_iterator &t)
        {
            cur=t.cur;
            src=t.src;
        }
        iterator(node *t,node *p)
        {
            cur=t;
            src=p;
        }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {
    private:
        node *cur;
        node *src;
    public:
        friend class iterator;
        friend class list;
        const_iterator(const const_iterator &t)
        {
            cur=t.cur;
            src=t.src;
        }
        const_iterator(const iterator &t)
        {
            cur=t.cur;
            src=t.src;
        }
        const_iterator(node *t,node *p)
        {
            cur=t;
            src=p;
        }
        const_iterator &operator=(const_iterator &tmp)
        {
            if (&tmp==this) return *this;
            cur=tmp.cur;
            src=tmp.src;
            return *this;
        }
        const_iterator operator++(int) {
            if (cur->next== nullptr) throw invalid_iterator();
            const_iterator tmp=*this;
            this->cur=this->cur->next;
            return tmp;
        }
        /**
         * ++iter
         */
        const_iterator & operator++() {
            if (cur->next== nullptr) throw invalid_iterator();
            this->cur=this->cur->next;
            return *this;
        }
        /**
         * iter--
         */
        const_iterator operator--(int) {
            if (cur->pre->pre== nullptr) throw invalid_iterator();
            const_iterator tmp=*this;
            this->cur=this->cur->pre;
            return tmp;
        }
        /**
         * --iter
         */
        const_iterator & operator--() {
            if (cur->pre->pre== nullptr) throw invalid_iterator();
            this->cur=this->cur->pre;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const {
            if (cur->pre==nullptr|| cur->next== nullptr) throw invalid_iterator();
            return *(cur->data);

        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const noexcept {
            if (cur->pre==nullptr|| cur->next== nullptr) throw invalid_iterator();
            return (cur->data);
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {
            if (cur==rhs.cur) return 1; else return 0;
        }
        bool operator==(const const_iterator &rhs) const {
            if (cur==rhs.cur) return 1; else return 0;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            if (cur==rhs.cur) return 0; else return 1;
        }
        bool operator!=(const const_iterator &rhs) const {
            if (cur==rhs.cur) return 0; else return 1;
        }
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() {
        head=new node;
        tail=new node;
        head->next=tail;
        head->pre=nullptr;
        tail->next=nullptr;
        tail->pre=head;
        len=0;
    }
    list(const list &other) {
        head=new node;
        tail=new node;
        head->next=tail;
        head->pre=nullptr;
        tail->next=nullptr;
        tail->pre=head;
        node *cur=other.head->next;
        len=0;
        while (cur!=other.tail)
        {
            node *p=new node(*(cur->data));
            insert(tail,p);
            cur=cur->next;
        }
    }
    /**
     * TODO Destructor
     */
    virtual ~list() {
       node *p;
       while (head)
       {
           p=head;
           head=head->next;
           delete p;
       }
       len=0;
    }
    /**
     * TODO Assignment operator
     */
    list &operator=(const list &other) {
        if (&other == this) return *this;
        node *t;
        while (head)
        {
            t=head;
            head=head->next;
            delete t;
        }
        head=new node;
        tail=new node;
        head->next=tail;
        head->pre=nullptr;
        tail->next=nullptr;
        tail->pre=head;
        node *cur=other.head->next;
        while (cur!=other.tail)
        {
            node *p=new node(*(cur->data));
            insert(tail,p);
            cur=cur->next;
        }
        return  *this;
    }
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T & front() const {
        if (len==0) throw container_is_empty();
        return *(head->next->data);
    }
    const T & back() const {
        if (len==0) throw container_is_empty();
        return *(tail->pre->data);
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(head->next,head);
    }
    const_iterator cbegin() const {
        return const_iterator(head->next,head);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(tail,head);
    }
    const_iterator cend() const {
        return const_iterator(tail,head);
    }
    /**
     * checks whether the container is empty.
     */
    virtual bool empty() const {
        if (len==0) return 1; else return 0;
    }
    /**
     * returns the number of elements
     */
    virtual size_t size() const {
        return len;
    }

    /**
     * clears the contents
     */
    virtual void clear() {
        if (head== nullptr) return;
        node *p=head->next,*q;
        while (p!=tail)
	    {
            q=p;
		    p=p->next;
		    delete q;
	    }
        head->next=tail;
        head->pre=nullptr;
        tail->next=nullptr;
        tail->pre=head;
        len=0;
    }
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    virtual iterator insert(iterator pos, const T &value) {
        if (pos.cur==head || pos.src!=head) throw invalid_iterator();
        node *t=new node(value);
        t->pre=pos.cur->pre;
        t->next=pos.cur;
        pos.cur->pre->next=t;
        pos.cur->pre=t;
        len++;
        return iterator(t,head);
    }
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    virtual iterator erase(iterator pos) {
        if (pos.cur==head || pos.cur==tail || pos.src!=head) throw invalid_iterator();
        if (len==0) throw container_is_empty();
        node *p=pos.cur->next;
        pos.cur->pre->next=p;
        p->pre=pos.cur->pre;
        p=pos.cur;
        pos++;
        delete p;
        len--;
        return pos;
    }
    /**
     * adds an element to the end
     */
    void push_back(const T &value) {
        node *t=new node(value);
        insert(tail,t);
    }
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back() {
        if (len==0) throw container_is_empty();
        node *p=tail->pre;
        p->pre->next=tail;
        tail->pre=p->pre;
        delete p;
        len--;
    }
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value) {
        node *t=new node(value);
        insert(head->next,t);
    }
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front() {
        if (len==0) throw container_is_empty();
        node *p=head->next;
        p->next->pre=head;
        head->next=p->next;
        delete p;
        len--;
    }
    /**
     * sort the values in ascending order with operator< of T
     */
    void sort() {
        T *a;
        std::allocator<T> alloc;
        a=alloc.allocate(len+1);
        node *t=head;
        for (int i=0;i<len;i++)
        {
            t=t->next;
            alloc.construct(a+i,*(t->data));
        }
        sjtu::sort<T>(a,a+len,[](const T &a,const T &b){ return a<b;});
        t=head;
        for (int i=0;i<len;i++)
        {
            t=t->next;
            *(t->data)=a[i];
            alloc.destroy(a+i);
        }
        alloc.deallocate(a,len+1);
    }
    
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void merge(list &other) {
        node *l1=head->next,*l2=other.head->next;
        while(l2!=other.tail && l1!=tail)
        {
            if (*(l2->data)<*(l1->data))
            {
                node *p=l2;
                while (l2!=other.tail && *(l2->data)<*(l1->data)) l2=l2->next;
                p->pre=l1->pre;
                l1->pre->next=p;
                l2->pre->next=l1;
                l1->pre=l2->pre;
            }
            else l1=l1->next;

        }
        if  (l2!=other.tail)
        {
            tail->pre->next = l2;
            l2->pre = tail->pre;
            other.tail->pre->next = tail;
            tail->pre = other.tail->pre;
        }
        len+=other.len;
        other.head->next=other.tail;
        other.tail->pre=other.head;
        other.len=0;
    }
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse() {
        node *p=tail->pre,*q=head,*tmp;
        while (p!=head)
        {
            q->next=p;
            tmp=p;
            p=p->pre;
            tmp->pre=q;
            q=q->next;
        }
        q->next=tail;
        tail->pre=q;
    }
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique() {
        node *p=head->next;
        while(p->next!=tail)
        {
            if (*(p->next->data)==*(p->data))
            {
                node *t=p->next;
                t->next->pre=p;
                p->next=t->next;
                delete t;
                len--;
            }
            else p=p->next;
        }
    }
};

}

#endif //SJTU_LIST_HPP