/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
	class Key,
	class T,
	class Compare = std::less<Key>
>
class map {
private:
    struct node
    {
        pair<const Key,T> *data;
        node *left, *right,*parent;
        int h;
        node ()
        {
			data = nullptr;
			left = nullptr;
			right = nullptr;
			parent=nullptr;
        }
		node (const pair<Key,T> &a,node *l=nullptr,node *r=nullptr,node *p=nullptr,int height=1)
		{
			right=r;
			left=l;
			data=new pair<Key,T>(a);
			h=height;
			parent=p;
		}	
		int imbalance(node *p){return (right?right->h:0)-(left?left->h:0);}
    };
	
public:
	node *root;
	size_t size;
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		node *position;
	public:
		friend class const_iterator;
		friend class map<Key,T,Compare>
		iterator() {
			position=nullptr;
			// TODO
		}
		iterator(const iterator &other) {
			position=other.position;
			// TODO
		}
		iterator(const const_iterator &other)
		{
			position=other.position;
		}
		iterator(node *other)
		{
			position=other;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) 
		{
			iterator t=*this;
			++(*this);
			return t;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() {
			if (position->right)
			{
				position=position->right;
				while (position->left) position=position->left;
			}
			else {
				node *before;
				do
				{
					before=position;
					position=position->parent;
				}while (position && before==position->right)
			}
			if (position==nullptr) throw sjtu::invalid_iterator();else return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator t=*this;
			--(*this);
			return t;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() {
			if (position->left)
			{
				position=position->left;
				while (position->right) position=position->right;
			}
			else {
				node *before;
				do
				{
					before=position;
					position=position->parent;
				}while (position && before==position->left)
			}
			if (position==nullptr) throw sjtu::invalid_iterator();else return *this;

		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const {
			return *position->data;
		}
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

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
			return position->data;
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
		node *position;
			// data members.
		public:
		friend class iterator;
		friend class map<Key,T,Compare>;
		const_iterator() {
			position=nullptr;
			// TODO
		}
		const_iterator(const const_iterator &other) {
			position=other.position;
			// TODO
		}
		const_iterator(const iterator &other) {
			position=other.position;
			// TODO
		}
		const_iterator(node *p)
		{
			position=p;
		}
		const_iterator operator++(int) 
		{
			const_iterator t=*this;
			++(*this);
			return t;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator & operator++() {
			if (position->right)
			{
				position=position->right;
				while (position->left) position=position->left;
			}
			else {
				node *before;
				do
				{
					before=position;
					position=position->parent;
				}while (position && before==position->right)
			}
			if (position==nullptr) throw sjtu::invalid_iterator();else return *this;
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			const_iterator t=*this;
			--(*this);
			return t;
		}
		/**
		 * TODO --iter
		 */
		const_iterator & operator--() {
			if (position->left)
			{
				position=position->left;
				while (position->right) position=position->right;
			}
			else {
				node *before;
				do
				{
					before=position;
					position=position->parent;
				}while (position && before==position->left)
			}
			if (position==nullptr) throw sjtu::invalid_iterator();else return *this;

		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		const value_type & operator*() const {
			return *position->data;
		}
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

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
			return position->data;
		}
			// And other methods in iterator.
			// And other methods in iterator.
	// Andother methods in iterator.
	};
	/**
	 * TODO two constructors
	 */
	map() {
		root=nullptr;
		size=0;
	}
	map(const map &other) {
		size=other.size;
		root=copy(other.root);
	}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {
		size=other.size;
		root=copy(other.root);
		return *this;
	}
	/**
	 * TODO Destructors
	 */
	~map() {
		clear();
		delete root;
	}
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key) {
		iterator res=find(key);
		if (res.position) return res.position->data->second; else throw sjtu::index_out_of_bound;
	}
	const T & at(const Key &key) const {
		iterator res=find(key);
		if (res.position) return res.position->data->second; else throw sjtu::index_out_of_bound;
	}
	/**
	 * TODO
	 * access specified element 
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {
		iterator res=find(key);
		if (res.position) return res.position->data->second; else 
		{
			pair<iterator,bool> m=insert(pair<Key,T>(key,T()));
			return m.first.position->data->second;
		}
	}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const {
		iterator res=find(key);
		if (res.position) return res.position->data->second; else throw sjtu::index_out_of_bound;
	}
	/**
	 * return a iterator to the beginning
	 */
	iterator begin() {
		node *pos=root;
		while (pos->left) pos=pos->left;
		return iterator(pos);
	}
	const_iterator cbegin() const {
		node *pos=root;
		while (pos->left) pos=pos->left;
		return const_iterator(pos);
	}
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end() {
		return iterator(root);
	}
	const_iterator cend() const {
		return const_iterator(root);
	}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const {
		return size==0;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {
		return size;
	}
	/**
	 * clears the contents
	 */
	void clear() {}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) {
		iterator res=find(value.first);
		if (res.position) return pair<iterator,bool>(res,0);
		node *parent=root;
		while (1)
		{
			if (parent==root || value.first<parent->data->first)
			{
				if (parent->left) parent=parent->left;
				else
				{
					parent->left=new node(value);
					res=iterator(parent->left);
					break;
				}
			}
			else{
				if (parent->right) parent=parent->right;
				else
				{
					parent->right=new node(value);
					res=iterator(parent->right);
					break;
				}
			}
		}
		int d=1;
		do
		{
			if (parent->h>d) break;
			parent->h=1+d;
			if (parent==root) break;
			if (parent->imbalance()<-1)
			{
				if (parent->left->imbalance()>0) ll(parent->left);
				rr(parent);
				break;
			}
			else if (parent->imbalance()>1)
			{
				if (parent->right->imbalance()<0) rr(parent->right);
				ll(parent);
				break;
			}
			d=parent->h;
			parent=parent->parent;
		} while (parent);
		return pair<iterator,bool>(res,1);
		
	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {
		if (pos==end() || pos.position==nullptr) throw invalid_iterator();
		iterator it(pos);
		it++;
		node *p=pos.position,*q;
		if (!p->left || !p->right) q=p; else q=it.position;
		node *s;
		if (q->left)
		{
			s=q->left;
			q->left=nullptr;
		}
		else
		{
			s=q->right;
			q->right=nullptr;
		}
		if (s) s->parent=q->parent;
		if (q==q->parent->left) q->parent->left=s; else q->parent->right=s;
		node *pa=q->parent;
		if (q!=p)
		{
			q->parent=p->parent;
			if (q->parent->left==p) q->parent->left=q; else q->parent->right=q;
			q->left=p->left;
			if (q->left) q->left->parent=q;
			q->right=p->right;
			if (q->right) q->right->parent=q;
			q->h=p->h;
			p->left=nullptr;p->right=nullptr;
		}
		if (pa==p) pa=q;
		node *fa;
		for (fa=pa;fa;fa=fa->parent)
		{
			fa->h=std::max(fa->right->h,fa->left->h)
		}
	}
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {
		node *rt=root;
		while (rt!=nullptr && !(rt->data->first>key || rt->data->first<key))
			if (rt->data->first>key) rt=rt->left; else rt=rt->right;
		if (rt==nullptr) return 0; else return 1; 
	}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) {
		node *rt=root;
		while (rt!=nullptr && !(rt->data->first>key || rt->data->first<key))
			if (rt->data->first>key) rt=rt->left; else rt=rt->right;
		if (rt==nullptr) return end(); else return iterator(rt); 
	}
	const_iterator find(const Key &key) const {
		node *rt=root;
		while (rt!=nullptr && rt->data->first!=key)
			if (rt->data->first>key) rt=rt->left; else rt=rt->right;
		if (rt==nullptr) return cend(); else return const_iterator(rt); 
	}
};

}

#endif
