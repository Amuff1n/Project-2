//Implementation of Binary Search Tree that inserts randomly
//templated with k type of key, v type of value,
//a comparision function that returns true if first key is less than second key,
//and an equals function that returns true if first key equals second key

//this BST is NOT self-balancing

#ifndef _BSTRAND_H_
#define _BSTRAND_H_
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
	class BST_Rand {
		public:
		BST_Rand();
		~BST_Rand();
		BST_Rand(const BST_Rand& other); //copy constructor
		BST_Rand<k,v,comp_func,eq_func>& operator= (const BST_Rand& other); //copy assignment
		Node<k,v> * do_copy(const Node<k,v>*& root); //helper method for copy stuff
		BST_Rand(BST_Rand&& other); //move constructor
		BST_Rand<k,v,comp_func,eq_func>& operator= (BST_Rand&& other); //move-assignment operator
		
		void insert(k key, v value);
		Node<k,v> * do_insert(Node<k,v> *& root, k key, v value);
		void remove(k key);
		Node<k,v> * do_remove(Node<k,v> *& root, k key);
		v& lookup(k key);
		v& do_lookup(Node<k,v> *& root, k key);
		
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
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Rand<k,v,comp_func,eq_func>::BST_Rand() {
		head = nullptr;
	}
	
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Rand<k,v,comp_func,eq_func>::~BST_Rand() {
		this->clear();
	}
	
	//--copy constructor
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Rand<k,v,comp_func,eq_func>::BST_Rand(const BST_Rand& other) {
		head = this->do_copy(other.head);
	}
	
	//--copy assignment
	//may have exception problems if other throws exceptions
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Rand<k,v,comp_func,eq_func>& BST_Rand<k,v,comp_func,eq_func>::operator=(const BST_Rand& other) {
		if (this != other) {
			this->clear();
			
			head = this->do_copy(other.head);
		}
		return *this;
	}
	
	//--do_copy helper
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	Node<k,v> * BST_Rand<k,v,comp_func,eq_func>::do_copy(const Node<k,v> *& root) {
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
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Rand<k,v,comp_func,eq_func>::BST_Rand(BST_Rand&& other) {
		head = other->head;
		other->head = nullptr;
	}
	
	//--move assignment
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	BST_Rand<k,v,comp_func,eq_func>& BST_Rand<k,v,comp_func,eq_func>::operator=(BST_Rand&& other) {
		if (this != other) {
			this->clear();
			head = other->head;
			other->head = nullptr;
		}
		return *this;
	}
	
	//--insert
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	void BST_Rand<k,v,comp_func,eq_func>::insert(k key, v value) {
		if (head == nullptr) {
			head = new Node<k,v>;
			head->key = key;
			head->value = value;
			return;
		}
		int size = this->size();
		int temp = std::rand() % (size+1);
		if (temp == 0) {
			//insert at root
			head = this->do_insert(head, key, value);
		}
		else {
			//insert at leaf
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
	}
	
	//--do_insert
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	Node<k,v> * BST_Rand<k,v,comp_func,eq_func>::do_insert(Node<k,v> *& root, k key, v value) {
		if (root == nullptr) {
			root = new Node<k,v>;
			root->key = key;
			root->value = value;
			return root;
		}
		
		if (comp_func(key,root->key)) {
			root->left = this->do_insert(root->left, key, value);
			//rotate root right
			class Node<k,v> *temp;
			temp = root->left;
			root->left = temp->right;
			temp->right = root;
			root = temp;
		}
		else {
			root->right = this->do_insert(root->right, key, value);
			//rotate root left
			class Node<k,v> *temp;
			temp = root->right;
			root->right = temp->left;
			temp->left = root;
			root = temp;
		}
		return root;
	}
	
	//--remove
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	void BST_Rand<k,v,comp_func,eq_func>::remove(k key) {
		head = this->do_remove(head, key);
	}
	
	//--do_remove
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	Node<k,v>* BST_Rand<k,v,comp_func,eq_func>::do_remove(Node<k,v> *& root, k key) {
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
	v& BST_Rand<k,v,comp_func,eq_func>::lookup(k key) {
		return this->do_lookup(head, key);
	}
	
	//--do_lookup 
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	v& BST_Rand<k,v,comp_func,eq_func>::do_lookup(Node<k,v> *& root, k key) {
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
	
	//--contains
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	bool BST_Rand<k,v,comp_func,eq_func>::contains(k key) {
		try {
			this->do_lookup(head, key);
		}
		catch (...) {
			return false;
		}
		return true;
	}
	
	//--is_empty
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	bool BST_Rand<k,v,comp_func,eq_func>::is_empty() {
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	
	//--is_full
	//should only be full if we can not physically allocate more memory for a new node
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	bool BST_Rand<k,v,comp_func,eq_func>::is_full() {
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
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	size_t BST_Rand<k,v,comp_func,eq_func>::size() {
		return this->do_size(head);
	}
	
	//--do_size
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	size_t BST_Rand<k,v,comp_func,eq_func>::do_size(Node<k,v> *& root) {
		if (root == nullptr) {
			return 0;
		}
		size_t temp = 1;
		temp += this->do_size(root->left);
		temp += this->do_size(root->right);
		return temp;
	}
	
	//--clear
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	void BST_Rand<k,v,comp_func,eq_func>::clear() {
		//should work by just calling remove on head
		while (head != nullptr) {
			this->remove(head->key);
		}
	}
	
	//--height
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	size_t BST_Rand<k,v,comp_func,eq_func>::height() {
		return this->do_height(head);
	}
	
	//--do_height
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	size_t BST_Rand<k,v,comp_func,eq_func>::do_height(Node<k,v> *& root) {
		if (root == nullptr) {
			return 0;
		}
		size_t temp = 1;
		temp += std::max(this->do_height(root->left), this->do_height(root->right));
		return temp;
	}
	
	//--balance
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	int BST_Rand<k,v,comp_func,eq_func>::balance() {
		return this->do_balance(head);
	}
	
	//--do_balance
	template <typename k, typename v, bool (*comp_func)(k,k), bool (*eq_func)(k,k)>
	int BST_Rand<k,v,comp_func,eq_func>::do_balance(Node<k,v> *& root) {
		if (root == nullptr) {
			return 0;
		}
		int left_height = this->do_height(root->left);
		int right_height = this->do_height(root->right);
		return left_height - right_height;
	}
}
#endif