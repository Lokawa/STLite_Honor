#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
private:
	struct Node
	{
		Node *left,*right;
		T *data;
		int npl;
		Node(const T &x,Node *l=nullptr,Node*r=nullptr)
		{
			left=l;
			right=r;
			data=new T(x);
			npl=-1;
		}
		~Node()
		{
			if (data) delete data;
			left=nullptr;
			right=nullptr;
		}
	};
	Node *root;
	int sizee;
	Node *copy(Node *p)
	{
		Node *t=new Node(*(p->data));
		if (p->left)
		{
			t->left=copy(p->left);
		}
		if (p->right)
		{
			t->right=copy(p->right);
		}
		return t;
	}
	void clear(Node *p)
	{
		if (p==nullptr) return;
		clear(p->left);
		clear(p->right);
		delete p;
		return;
	}
	Node* merge(Node* root1,Node* root2)
	{
		if (root1==nullptr) return root2;
		if (root2==nullptr) return root1;
		Compare cmp;
		if (cmp(*(root1->data),*(root2->data)))
		{
			Node *t=root1;
			root1=root2;
			root2=t;
		}
		if (root2->right==nullptr)
		{
			root2->right=root1;
			return root2;
		}
		root2->right=merge(root1,root2->right);
		if (root2->left==nullptr || root2->left->npl<root2->right->npl)
		{
			Node *t=root2->left;
			root2->left=root2->right;
			root2->right=t;
		}
		if (root2->left==nullptr || root2->right==nullptr) root2->npl=0;
		else if (root2->left->npl<root2->right->npl) root2->npl=root2->left->npl+1;
		else root2->npl=root2->right->npl+1;
		return root2;
	}

public:
	/**
	 * TODO constructors
	 */
	priority_queue() {
		sizee=0;
		root=nullptr;
	}
	priority_queue(const priority_queue &other) {
		sizee=other.sizee;
		root=copy(other.root);
	}
	/**
	 * TODO deconstructor
	 */
	~priority_queue() {
		clear(root);
		sizee=0;
		root=nullptr;
	}
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other) {
		if (this==&other) return *this;
		clear(root);
		sizee=other.sizee;
		root=copy(other.root);
		return *this;
	}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {
		if (sizee==0) throw container_is_empty();
		return *(root->data);
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
		Node *t=new Node(e);
		sizee++;
		merge(root,t);
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {
		if (sizee==0) throw container_is_empty();
		Node *t=root;
		root=merge(root->left,root->right);
		delete t;
		sizee--;
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
		return sizee;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
		if (sizee==0) return true; else return false;
	}
	/**
	 * merge two priority_queues with at least O(logn) complexity.
	 * clear the other priority_queue.
	 */
	void merge(priority_queue &other) {
		merge(root,other.root);
		sizee+=other.sizee;
		other.sizee=0;
		other.root=nullptr;
	}
};

}

#endif