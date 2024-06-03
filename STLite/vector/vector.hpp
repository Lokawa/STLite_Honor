#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
public:
    T *data_head,*data_tail;
    int len;
    std::allocator<T> alloc;
    /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class const_iterator;
    class iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        const vector<T> *obj;
        int position;
    public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator(const vector<T> *t,int n)
        {
            position=n;
            obj=t;
        }
        iterator(const iterator& t)
        {
            position=t.position;
            obj=t.obj;
        }
        iterator(const const_iterator& t)
        {
            position=t.position;
            obj=t.obj;
        }
        iterator operator+(const int &n) const{
         //   if (position>=obj->len-n) throw sjtu::index_out_of_bound();
            return iterator(this->obj,this->position+n);
            //TODO
        }
        iterator operator-(const int &n) const {
          //  if (position<n) throw sjtu::index_out_of_bound();
            return iterator(this->obj,this->position-n);
            //TODO
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if (obj->data!=rhs.obj->data) throw sjtu::invalid_iterator();
            return this->position-rhs.position;
            //TODO
        }
        iterator& operator+=(const int &n) {
     //       if (position>=obj->len-n) throw sjtu::index_out_of_bound();
            this->position+=n;
            return *this;
            //TODO
        }
        iterator& operator-=(const int &n) {
         //   if (position<n) throw sjtu::index_out_of_bound();
            this->position-=n;
            return *this;
            //TODO
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
           // if (position>=obj->len-1) throw sjtu::index_out_of_bound();
            iterator p=*this;
            this->position++;
            return p;
        }
        /**
         * TODO ++iter
         */
        iterator& operator++() {
          //  if (position>=obj->len-1) throw sjtu::index_out_of_bound();
            this->position++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
          //  if (position<1) throw sjtu::index_out_of_bound();
            iterator p=*this;
            this->position--;
            return p;
        }
        /**
         * TODO --iter
         */
        iterator& operator--() {
         //   if (position<1) throw sjtu::index_out_of_bound();
            this->position--;
            return *this;
        }
        /**
         * TODO *it
         */
        T& operator*() const{
            return *(obj->data_head+position);
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return position==rhs.position;
        }
        bool operator==(const const_iterator &rhs) const {
            return position==rhs.position;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return position!=rhs.position;
        }
        bool operator!=(const const_iterator &rhs) const {
            return position!=rhs.position;
        }
        friend const_iterator;
        friend vector<T>;
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     */
    class const_iterator {
    private:
        int position;
        const vector<T> *obj;
    public:
        const_iterator(const vector<T> *t,int n)
        {
            position=n;
            obj=t;
        }
        const_iterator(const const_iterator& t)
        {
            position=t.position;
            obj=t.obj;
        }
        const_iterator(const iterator& t)
        {
            position=t.position;
            obj=t.obj;
        }
        T& operator*() const{
            return *(obj->data_head+position);
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return position==rhs.position;
        }
        bool operator==(const const_iterator &rhs) const {
            return position==rhs.position;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return position!=rhs.position;
        }
        bool operator!=(const const_iterator &rhs) const {
            return position!=rhs.position;
        }
        friend iterator;
        friend vector<T>;
        const_iterator operator++(int) {
         //   if (position>=obj->len-1) throw sjtu::index_out_of_bound();
            iterator p=*this;
            this->position++;
            return p;
        }
        /**
         * TODO ++iter
         */
        const_iterator& operator++() {
          //  if (position>=obj->len-1) throw sjtu::index_out_of_bound();
            this->position++;
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
         //  if (position<1) throw sjtu::index_out_of_bound();
            iterator p=*this;
            this->position--;
            return p;
        }
        /**
         * TODO --iter
         */
        const_iterator& operator--() {
          //  if (position<1) throw sjtu::index_out_of_bound();
            this->position--;
            return *this;
        }
        /**
         * TODO *it
         */
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    vector() {
        len=10;
        data_head=alloc.allocate(len);
        data_tail=data_head;
    }
    vector(const vector &other) {
        len=other.len;
        data_head=alloc.allocate(len);
        data_tail=data_head;
        for (int i=0;i<other.size();i++)
        {
            alloc.construct(data_tail,other[i]);
            data_tail++;
        }
    }
    /**
     * TODO Destructor
     */
    ~vector() {
        clear();
    }
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other) {
        if (this!=&other)
        {
            clear();
            len=other.len;
            data_head=alloc.allocate(len);
            data_tail=data_head;
            for (int i=0;i<other.size();i++)
            {
                alloc.construct(data_tail,other[i]);
                data_tail++;
            }  

        }
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos) {
        if (pos<0 || pos>=len) throw index_out_of_bound();
        return *(data_head+pos);
    }
    const T & at(const size_t &pos) const {
        if (pos<0 || pos>=len) throw index_out_of_bound();
        return *(data_head+pos);
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos) {
        if (pos<0 || pos>=len) throw index_out_of_bound();
        return *(data_head+pos);
    }
    const T & operator[](const size_t &pos) const {
        if (pos<0 || pos>=len) throw index_out_of_bound();
        return *(data_head+pos);
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const {
        if (size()==0) throw container_is_empty();
        return *data_head;
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const {
        if (size()==0) throw container_is_empty();
        return *(data_tail-1);
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        iterator t(this,0);
        return t;
    }
    const_iterator cbegin() const {
        const_iterator t(this,0);
        return t;
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        iterator t(this,size());
        return t;
    }
    const_iterator cend() const {
        const_iterator t(this,size());
        return t;
    }

    /**
     * checks whether the container is empty
     */
    bool empty() const {
        if (len==0) return 1; else return 0;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return data_tail-data_head;
    }
    /**
     * clears the contents
     */
    void clear() {
        T *p(data_head);
        while (data_head!=data_tail)
        {
            alloc.destroy(data_head);
            data_head++;
        }
        alloc.deallocate(p,len);
        len=0;
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value) {
        
        T tmp(*(data_tail-1));
        if (size()==len) doublespace();
        alloc.construct(data_tail,tmp);
        data_tail++;
        for (int i=size()-2;i>pos.position;i--)
            this->at(i)=this->at(i-1);
        this->at(pos.position)=value;
        return pos;
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if (ind>len) throw index_out_of_bound();
        if (size()+1==len) doublespace();
        T tmp(*(data_tail-1));
        alloc.construct(data_tail,tmp);
        data_tail++;
        for (int i=size()-2;i>ind;i--)
            this->at(i)=this->at(i-1);
        this->at(ind)=value;
        return iterator(this,ind);
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        if (pos!=end()) 
            for (int i=pos.position;i<size()-1;i++)
                this->at(i)=this->at(i+1);
        alloc.destroy(data_tail);
        data_tail--;
        return pos;
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if (ind>=len) throw index_out_of_bound();
        for (int i=ind;i<size()-1;i++)
            this->at(i)=this->at(i+1);
        alloc.destroy(data_tail);
        data_tail--;
        return iterator(this,ind);
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        if (size()==len) doublespace();
        alloc.construct(data_tail,value);
        data_tail++;
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if (size()==0) throw container_is_empty();
        data_tail--;
        alloc.destroy(data_tail);
    }
    void doublespace()
    {
        vector<T> tmp(*this);
        clear();
        len=tmp.len*2;
        data_head=alloc.allocate(len);
        data_tail=data_head;
        for (int i=0;i<tmp.len;i++)
        {
            alloc.construct(data_tail,tmp[i]);
            data_tail++;
        }
    }
};


}

#endif