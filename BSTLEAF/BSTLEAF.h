//Implementation of a Binary Search Tree that inserts at Leaf
//templated with k type of key, v type of value,
//a comparision function that returns true if first key is less than second key,
//and an equals function that returns true if first key equals second key

//this BST is NOT self-balancing

//comeback to removing and clearing functions because they crash pocketcpp
//but check out fine in ubuntu with valgrind :thinking:

#ifndef	_BSTLEAF_H_
#define _BSTLEAF_H_
#include <stdexcept>

namespace cop3530 {
	
	#ifndef NODE_H_
	#define NODE_H_
	template <typename k, typename v>
	class Node {
		public:
		k key;
		v value;
		Node<k,v> * left = nullptr;
		Node<k,v> * right = nullptr;
	};
	#endif
	
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	class BSTLEAF {
		public:
		BSTLEAF();
		~BSTLEAF();
		BSTLEAF(const BSTLEAF& other); //copy constructor
		BSTLEAF<k,v,comp_func,eq_func>& operator= (const BSTLEAF& other); //copy assignment
		Node<k,v> * do_copy(const Node<k,v>* root); //helper method for copy stuff
		BSTLEAF(BSTLEAF&& other); //move constructor
		BSTLEAF<k,v,comp_func,eq_func>& operator= (BSTLEAF&& other); //move-assignment operator
		
		void insert(k key, v value);
		void remove(k key);
		Node<k,v> * do_remove(Node<k,v> *& root, k key);
		v& lookup(k key);
		const v& lookup(k key) const;
		v& do_lookup(Node<k,v> *& root, k key);
		const v& do_lookup_const(const Node<k,v> * root, k key) const;
		
		bool contains(k key);
		bool is_empty();
		bool is_full();
		size_t size();
		size_t do_size(Node<k,v> *& root);
		void clear();
		size_t height();
		size_t do_height(Node<k,v> *& root);
		//since balance can be negative, and size_t is unsigned, return int instead
		int balance();
		int do_balance(Node<k,v> *& root);
		
		private:
		Node<k,v> * head = nullptr;
	};
	
	//--constructors and destructors
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	BSTLEAF<k,v,comp_func,eq_func>::BSTLEAF() {
		head = nullptr;
	}
	
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	BSTLEAF<k,v,comp_func,eq_func>::~BSTLEAF() {
		this->clear();
	}
	
	//--copy constructor
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	BSTLEAF<k,v,comp_func,eq_func>::BSTLEAF(const BSTLEAF& other) {
		head = this->do_copy(other.head);
	}
	
	//--copy assignment
	//may have exception problems if other throws exceptions
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	BSTLEAF<k,v,comp_func,eq_func>& BSTLEAF<k,v,comp_func,eq_func>::operator=(const BSTLEAF& other) {
		if (this != &other) {
			this->clear();
			
			head = this->do_copy(other.head);
		}
		return *this;
	}
	
	//--do_copy helper
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	Node<k,v> * BSTLEAF<k,v,comp_func,eq_func>::do_copy(const Node<k,v> * root) {
		if (root == nullptr) {
			return nullptr;
		}
		//make new node and copy
		class Node<k,v> *temp;
		temp = new Node<k,v>;
		temp->key = root->key;
		temp->value = root->value;
		
		//do_copy on children
		temp->left = this->do_copy(root->left);
		temp->right = this->do_copy(root->right);
		
		return temp;
	}
	
	//--move constructor
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	BSTLEAF<k,v,comp_func,eq_func>::BSTLEAF(BSTLEAF&& other) {
		head = other.head;
		other.head = nullptr;
	}
	
	//--move assignment
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	BSTLEAF<k,v,comp_func,eq_func>& BSTLEAF<k,v,comp_func,eq_func>::operator=(BSTLEAF&& other) {
		if (this != &other) {
			this->clear();
			head = other.head;
			other.head = nullptr;
		}
		return *this;
	}
	
	//--insert
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	void BSTLEAF<k,v,comp_func,eq_func>::insert(k key, v value) {
		if (head == nullptr) {
			head = new Node<k,v>;
			head->key = key;
			head->value = value;
			head->left = nullptr;
			head->right = nullptr;
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
		if (key == parent->key) {
			parent->value = value;
			return;
		}
		temp = new Node<k,v>;
		temp->key = key;
		temp->value = value;
		temp->left = nullptr;
		temp->right = nullptr;
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
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	void BSTLEAF<k,v,comp_func,eq_func>::remove(k key) {
		head = this->do_remove(head, key);
	}
	
	//--do_remove
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	Node<k,v>* BSTLEAF<k,v,comp_func,eq_func>::do_remove(Node<k,v> *& root, k key) {
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
				delete temp;
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
			
		}
		return root;	
	}
	
	//--lookup 
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	v& BSTLEAF<k,v,comp_func,eq_func>::lookup(k key) {
		return this->do_lookup(head, key);
	}
	
	//--lookup const
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	const v& BSTLEAF<k,v,comp_func,eq_func>::lookup(k key) const {
		return this->do_lookup_const(head, key);
	}
	
	//--do_lookup 
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	v& BSTLEAF<k,v,comp_func,eq_func>::do_lookup(Node<k,v> *& root, k key) {
		if (root == nullptr) {
			throw std::runtime_error("key does not exist in BST");

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
	
	//--do_lookup const
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	const v& BSTLEAF<k,v,comp_func,eq_func>::do_lookup_const(const Node<k,v> * root ,k key) const {
		if (root == nullptr) {
			throw std::runtime_error("key does not exist in BST");
		}
		if (eq_func(key, root->key)) {
			return root->value;
		}
		if (comp_func(key, root->key)) {
			return this->do_lookup_const(root->left, key);
		}
		else {
			return this->do_lookup_const(root->right, key);
		}
	}
	
	//--contains
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	bool BSTLEAF<k,v,comp_func,eq_func>::contains(k key) {
		try {
			this->do_lookup(head, key);
		}
		catch (...) {
			return false;
		}
		return true;
	}
	
	//--is_empty
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	bool BSTLEAF<k,v,comp_func,eq_func>::is_empty() {
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	
	//--is_full
	//should only be full if we can not physically allocate more memory for a new node
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	bool BSTLEAF<k,v,comp_func,eq_func>::is_full() {
		class Node<k,v> *temp;
		try {
			
			temp = new Node<k,v>; //would throw an exception with 'new' if out of memory
		}
		catch (...) {
			return true;
		}
		delete temp;
		return false;
	}
	
	//--size
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	size_t BSTLEAF<k,v,comp_func,eq_func>::size() {
		return this->do_size(head);
	}
	
	//--do_size
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	size_t BSTLEAF<k,v,comp_func,eq_func>::do_size(Node<k,v> *& root) {
		if (root == nullptr) {
			return 0;
		}
		size_t temp = 1;
		temp += this->do_size(root->left);
		temp += this->do_size(root->right);
		return temp;
	}
	
	//--clear
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	void BSTLEAF<k,v,comp_func,eq_func>::clear() {
		//should work by just calling remove on head
		while (head != nullptr) {
			this->remove(head->key);
		}
	}
	
	//--height
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	size_t BSTLEAF<k,v,comp_func,eq_func>::height() {
		return this->do_height(head);
	}
	
	//--do_height
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	size_t BSTLEAF<k,v,comp_func,eq_func>::do_height(Node<k,v> *& root) {
		if (root == nullptr) {
			return 0;
		}
		size_t temp = 1;
		temp += std::max(this->do_height(root->left), this->do_height(root->right));
		return temp;
	}
	
	//--balance
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	int BSTLEAF<k,v,comp_func,eq_func>::balance() {
		return this->do_balance(head);
	}
	
	//--do_balance
	template <typename k, typename v, bool (*comp_func)(const k&,const k&), bool (*eq_func)(const k&,const k&)>
	int BSTLEAF<k,v,comp_func,eq_func>::do_balance(Node<k,v> *& root) {
		if (root == nullptr) {
			return 0;
		}
		int left_height = this->do_height(root->left);
		int right_height = this->do_height(root->right);
		return left_height - right_height;
	}
	
}
#endif