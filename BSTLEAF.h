//Implementation of a Binary Search Tree that inserts at Leaf
//templated with k type of key, v type of value,
//a comparision function that returns true if first key is less than second key,
//and an equals function that returns true if first key equals second key

//this BST is NOT self-balancing

#ifndef	_BSTLEAF_H_
#define _BSTLEAF_H_
#include <stdexcept>

namespace cop3530 {
	
	template <typename k, typename v>
	class Node {
		public:
		k key;
		v value;
		Node<k,v> * left = nullptr;
		Node<k,v> * right = nullptr;
	};
	
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	class BST_Leaf {
		public:
		BST_Leaf();
		~BST_Leaf();
		BST_Leaf(const BST_Leaf& other); //copy constructor
		BST_Leaf<k,v,comp_func,eq_func>& operator= (const BST_Leaf& other); //copy assignment
		BST_Leaf(BST_Leaf&& other); //move constructor
		BST_Leaf<k,v,comp_func,eq_func>& operator= (BST_Leaf&& other); //move-assignment operator
		
		void insert(k key, v value);
		void remove(k key);
		Node<k,v> * do_remove(Node<k,v> *& root, k key);
		v& lookup(k key);
		v& do_lookup(Node<k,v> *& root, k key);
		
		
		//bool contains(k key);
		//bool is_empty();
		//bool is_full();
		//size_t size();
		void clear();
		//size_t height();
		//size_t balance_factor();
		
		
		private:
		Node<k,v> * head = nullptr;
	};
	
	//--constructors and destructors
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Leaf<k,v,comp_func,eq_func>::BST_Leaf() {
		head = nullptr;
	}
	
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Leaf<k,v,comp_func,eq_func>::~BST_Leaf() {
		this->clear();
	}
	
	//--copy constructor
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Leaf<k,v,comp_func,eq_func>::BST_Leaf(const BST_Leaf& other) {
		class Node<k,v> *temp;
		temp = other.head;
		//TODO insert every key value pair from other to construct new tree
	}
	
	//--copy assignment
	//may have exception problems if other throws exceptions
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Leaf<k,v,comp_func,eq_func>& BST_Leaf<k,v,comp_func,eq_func>::operator=(const BST_Leaf& other) {
		if (this != other) {
			this->clear();
			class Node<k,v> *temp;
			temp = other.head;
			//TODO insert every key value pair from other to construct new tree
		}
		return *this;
	}
	
	//--move constructor
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Leaf<k,v,comp_func,eq_func>::BST_Leaf(BST_Leaf&& other) {
		head = other->head;
		other->head = nullptr;
	}
	
	//--move assignment
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Leaf<k,v,comp_func,eq_func>& BST_Leaf<k,v,comp_func,eq_func>::operator=(BST_Leaf&& other) {
		if (this != other) {
			this->clear();
			head = other->head;
			other->head = nullptr;
		}
		return *this;
	}
	
	//--insert
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	void BST_Leaf<k,v,comp_func,eq_func>::insert(k key, v value) {
		if (head == nullptr) {
			head = new Node<k,v>;
			head->key = key;
			head->value = value;
			return;
		}
		
		//start search for key
		class Node<k,v> *parent, *temp;
		parent = head;
		temp = parent;
		while (temp != nullptr) {
			parent = temp;
			temp = comp_func(key, temp->key) ? temp->left : temp->right;
		}
		
		temp = new Node<k,v>;
		temp->key = key;
		temp->value = value;
		//if temp is less than parent, left child
		if (comp_func(key, parent->key)) {
			parent->left = temp;
		}
		//else it is parent's right child
		else {
			parent->right = temp;
		}
	}
	
	//--remove
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	void BST_Leaf<k,v,comp_func,eq_func>::remove(k key) {
		head = this->do_remove(head, key);
	}
	
	//--do_remove
	//TODO something breaks when you remove the head
	//you can still lookup the head but links to the subtrees are broken?
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	Node<k,v>* BST_Leaf<k,v,comp_func,eq_func>::do_remove(Node<k,v> *& root, k key) {
		class Node<k,v> *temp;
		if (root == nullptr) {
			return nullptr;
		}
		if (comp_func(key,root->key)) {
			root->left = do_remove(root->left, key);
		}
		if (comp_func(root->key, key)) {
			root->right = do_remove(root->right, key);
		}
		if (eq_func(key, root->key)) {
			temp = root;
			if (root->right == nullptr) {
				root = root->left;
			}
			else {
				//find minimum value in right subtree
				class Node<k,v> *min;
				min = root->right;
				while (min->left != nullptr) {
					min = min->left;
				}
				//replace root with min value
				root->key = min->key;
				root->value = min->value;
				//do_remove on right subtree with current root's key, since there is now a duplicate
				do_remove(root->right, root->key);
			}
			delete temp;
		}
		return root;	
	}
	
	//--lookup 
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	v& BST_Leaf<k,v,comp_func,eq_func>::lookup(k key) {
		return this->do_lookup(head, key);
	}
	
	//--do_lookup 
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	v& BST_Leaf<k,v,comp_func,eq_func>::do_lookup(Node<k,v> *& root, k key) {
		if (root == nullptr) {
			throw std::invalid_argument("key does not exist in BST");
		}
		if (eq_func(key, root->key)) {
			return root->value;
		}
		if (comp_func(key, root->key)) {
			return this->do_lookup(root->left, key);
		}
		else {
			return this->do_lookup(root->right, key);
		}
	}
	
	//--clear
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	void BST_Leaf<k,v,comp_func,eq_func>::clear() {
		//should work by just calling remove on head
		while (head != nullptr) {
			this->remove(head->key);
		}
	}
}
#endif