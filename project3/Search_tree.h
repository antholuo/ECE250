/*****************************************
 * UW User ID:  a26luo
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2022
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

// ? what does this even do
#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include <cassert>

#include "Exception.h"
#include "ece250.h"

template <typename Type>
class Search_tree {
   public:
	class Iterator;

   private:
	class Node {
	   public:
		Type node_value;
		int tree_height;  // ! And this is the actual HEIGHT of the particular node

		// mine
		Type nv();

		// The left and right sub-trees
		// * these are heads of the sub-trees
		Node *left_tree;
		Node *right_tree;

		// Hint as to how you can create your iterator
		// Point to the previous and next nodes in linear order
		Node *previous_node;
		Node *next_node;

		// Member functions
		Node(Type const & = Type());

		void update_height();
		int balance_factor();

		int height() const;
		bool is_leaf() const;
		Node *front();
		Node *back();
		Node *find(Type const &obj);

		void clear();
		// todo: implement these
		bool insert_internal(Type const &obj, Node *&to_this);  // should be done?
		bool erase_internal(Type const &obj, Node *&to_this);
	};

	Node *root_node;
	int tree_size;  // ? what is this one supposed to do...
	// ! WAIT IS IT THE LINKED LIST SIZE? -> needed for iterators
	// - and so it has nothing to do with the actual height of the tree

	// todo: double check linked list creation
	Node *front_sentinel;
	Node *back_sentinel;
   private:
	// todo: implement these
	static void balance(Node *&curr_node);
	static void rotate_left(Node *&curr_node);
	static void rotate_right(Node *&curr_node);
	// Hint as to how to start your linked list of the nodes in order
   public:
	static void printBT(const std::string &prefix,
	                    const Search_tree<Type>::Node *node, bool isLeft);
	class Iterator {
	   private:
		Search_tree *containing_tree;
		Node *current_node;
		bool is_end;

		// The constructor is private so that only the search tree can create an
		// iterator
		Iterator(Search_tree *tree, Node *starting_node);

	   public:
		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		Type operator*() const;
		Iterator &operator++();
		Iterator &operator--();
		bool operator==(Iterator const &rhs) const;
		bool operator!=(Iterator const &rhs) const;

		// Make the search tree a friend so that it can call the constructor
		friend class Search_tree;
	};

	// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
	Search_tree();
	~Search_tree();

	bool empty() const;
	int size() const;
	int height() const;

	Type front() const;
	Type back() const;

	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	Iterator find(Type const &);

	void clear();
	bool insert(Type const &);
	bool erase(Type const &);

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Search_tree<T> const &);
};

//////////////////////////////////////////////////////////////////////
//               Search Tree Private Member Functions               //
//////////////////////////////////////////////////////////////////////
template <typename Type>
void Search_tree<Type>::rotate_right(Node *&curr_node) {
	// right rotation
	auto tmp = curr_node->left_tree;  // ? why do we use auto
	curr_node->left_tree = tmp->right_tree;
	tmp->right_tree = curr_node;
	curr_node = tmp;
}

template <typename Type>
void Search_tree<Type>::rotate_left(Node *&curr_node) {
	auto tmp = curr_node->right_tree;
	curr_node->right_tree = tmp->left_tree;
	tmp->left_tree = curr_node;
	curr_node = tmp;
}

template <typename Type>
void Search_tree<Type>::balance(Node *&curr_node) {
	// Update height for use in balanceFactor
	// ! double check this later
	// * not strictly necessary
	// curr_node->update_height();

	// Left heavy
	if (curr_node->balance_factor() < -1) {
		// Case: left-right
		if (curr_node->left_tree->balance_factor() > 0) {
			rotate_left(curr_node->left_tree);
		}
		rotate_right(curr_node);
	}

	// Right heavy
	else if (curr_node->balance_factor() > 1) {
		// Case: right-left
		if (curr_node->right_tree->balance_factor() < 0){
			rotate_right(curr_node->right_tree);
		}
		rotate_left(curr_node);
	}

	if (curr_node->right_tree) curr_node->right_tree->update_height();
	if (curr_node->left_tree) curr_node->left_tree->update_height();
	curr_node->update_height();
}

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the froat the nt and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree()
    : root_node(nullptr),
      tree_size(0),
      front_sentinel(new Search_tree::Node(Type())),
      back_sentinel(new Search_tree::Node(Type())) {
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();  // might as well use it...
	delete front_sentinel;
	delete back_sentinel;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return (root_node == nullptr);
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if (empty()) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if (empty()) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator(this, back_sentinel)
	               : Iterator(this, root_node->front());
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator(this, back_sentinel);
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator(this, front_sentinel)
	               : Iterator(this, root_node->back());
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator(this, front_sentinel);
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find(Type const &obj) {
	if (empty()) {
		return Iterator(this, back_sentinel);
	}

	typename Search_tree<Type>::Node *search_result = root_node->find(obj);

	if (search_result == nullptr) {
		return Iterator(this, back_sentinel);
	} else {
		return Iterator(this, search_result);
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if (!empty()) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

// TODO: figure out how to add in the LL part of this.
template <typename Type>
bool Search_tree<Type>::insert(Type const &obj) {
	if ( empty() ) {
		// we have to include this case here because we don't want to create a linked list with weird swapping.
		root_node = new Search_tree::Node( obj );
		front_sentinel->next_node = root_node;
		root_node->next_node = back_sentinel;
		root_node->previous_node = front_sentinel;
		back_sentinel->previous_node = root_node;
		tree_size = 1;
		return true;
	} else if ( root_node->insert_internal( obj, *&root_node ) ) {
		++tree_size;
		return true;
	} else {
		return false;
	}
	return false;
}

template <typename Type>
bool Search_tree<Type>::erase(Type const &obj) {
	if (!empty() && root_node->erase_internal(obj, root_node)) {
		--tree_size;
		return true;
	} else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node(Type const &obj)
    : node_value(obj),
      left_tree(nullptr),
      right_tree(nullptr),
      next_node(nullptr),
      previous_node(nullptr),
      tree_height(0) {
	// does nothing
}

template <typename Type>
Type Search_tree<Type>::Node::nv() {
	return this->node_value;
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max(left_tree->height(), right_tree->height()) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::balance_factor() {
	return (right_tree ? right_tree->height() + 1 : 0) -
	       (left_tree ? left_tree->height() + 1 : 0);
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return (this == nullptr) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ((left_tree == nullptr) && (right_tree == nullptr));
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return (left_tree == nullptr) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return (right_tree == nullptr) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find(
    Type const &obj) {
	if (obj == node_value) {
		return this;
	} else if (obj < node_value) {
		return (left_tree == nullptr) ? nullptr : left_tree->find(obj);
	} else {
		return (right_tree == nullptr) ? nullptr : right_tree->find(obj);
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if (left_tree != nullptr) {
		left_tree->clear();
	}

	if (right_tree != nullptr) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert_internal(
    Type const &obj, Search_tree<Type>::Node *&to_this) {
	// assuming no duplicates for now
	// TODO: add in code for duplicate
	// TODO: change update_height() to be balance() (balance will automatically
	// update heights)at the
	if (obj < node_value) {
		// ! add in a function that allows us to keep insert into the LL simultaneously
		if ( left_tree == nullptr ) {
				// we have found space for the node!
		        left_tree = new Search_tree<Type>::Node( obj );
		        update_height();
				// insert into LL before balancing? (since we have inserted it in order, we don't want the balance to potentially screw up balancing)
				// * plus, the LL order can't be changed by balancing anyways.

				// A <-> C ==> A <-> B <-> C
				to_this->previous_node->next_node = left_tree; // A -> B // ! seg fault here
				left_tree->previous_node = to_this->previous_node; // A <-> B
				to_this->previous_node = left_tree;	// A <-> B <- C
				left_tree->next_node = to_this;	// A <-> B <-> C

				balance(to_this);
		        return true;
		} else { 
			if (left_tree->insert_internal(obj, left_tree)) {
				update_height();
				balance(to_this);
				 return true;
			} else {
				return false;
			}
		}
	} else if (obj > node_value) {
		if ( right_tree == nullptr ) {
				// we have found space for the node!
		        right_tree = new Search_tree<Type>::Node( obj );
		    	update_height();
				// no need to balance
		        return true;
		} else {
			if (right_tree->insert_internal(obj, right_tree)) {
				update_height();
				balance(to_this);
				 return true;
			} else {
				return false;
			}
		}
	} else {
		// duplicate case.
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase_internal(
    Type const &obj, Search_tree<Type>::Node *&to_this) {
	bool result;
	if (obj < node_value) {
		if (left_tree == nullptr) {
			return false;
		} else {
			if (left_tree->erase(obj, left_tree)) {
				update_height();
				return true;
			}

			return false;
		}
	} else if (obj > node_value) {
		if (right_tree == nullptr) {
			return false;
		} else {
			if (right_tree->erase(obj, right_tree)) {
				update_height();
				return true;
			}

			return false;
		}
	} else {
		assert(obj == node_value);

		if (is_leaf()) {
			to_this = nullptr;
			delete this;
		} else if (left_tree == nullptr) {
			to_this = right_tree;
			delete this;
		} else if (right_tree == nullptr) {
			to_this = left_tree;
			delete this;
		} else {
			node_value = right_tree->front()->node_value;
			right_tree->erase(node_value, right_tree);
			update_height();
		}

		return true;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator(
    Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node)
    : containing_tree(tree), current_node(starting_node) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	// This is done for you...
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &
Search_tree<Type>::Iterator::operator++() {
	// Update the current node to the node containing the next higher value
	// If we are already at end do nothing

	// Your implementation here, do not change the return value

	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &
Search_tree<Type>::Iterator::operator--() {
	// Update the current node to the node containing the next smaller value
	// If we are already at either rend, do nothing

	// Your implementation here, do not change the return value

	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==(
    typename Search_tree<Type>::Iterator const &rhs) const {
	// This is done for you...
	return (current_node == rhs.current_node);
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=(
    typename Search_tree<Type>::Iterator const &rhs) const {
	// This is done for you...
	return (current_node != rhs.current_node);
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename Type>
void Search_tree<Type>::printBT(const std::string &prefix,
                                const Search_tree<Type>::Node *node,
                                bool isLeft) {
	if (node != nullptr) {
		std::cout << prefix;
		std::cout << (isLeft ? "├──" : "└──");

		// print the value of the node
		std::cout << node->node_value << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "│   " : "    "), node->right_tree, true);
		printBT(prefix + (isLeft ? "│   " : "    "), node->left_tree, false);
	}
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Search_tree<T> const &list) {
	Search_tree<T>::printBT("", list.root_node, false);
	return out;
}

#endif
