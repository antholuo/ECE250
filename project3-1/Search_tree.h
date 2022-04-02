/*****************************************
 * UW User ID:  a26luo
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2022
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>

template <typename Type>
class Search_tree {
	public:
		class Iterator;

	private:
		class Node {
			public:
				Type node_value;
				int tree_height;

				// The left and right sub-trees
				Node *left_tree;
				Node *right_tree;

				// Hint as to how you can create your iterator
				// Point to the previous and next nodes in linear order
				Node *previous_node;
				Node *next_node;

				// Member functions
				Node( Type const & = Type() );

				void update_height();
				int balanceFactor() const;

				int height() const;
				bool is_leaf() const;
				Node *front();
				Node *back();
				Node *find( Type const &obj );

				void clear();
				bool insert( Type const &obj, Node *&to_this );
				bool erase( Type const &obj, Node *&to_this );
		};

		Node *root_node;
		int tree_size; // number of nodes in the tree

		// Hint as to how to start your linked list of the nodes in order 
		Node *front_sentinel;
		Node *back_sentinel;

		// functions to rotate our trees
		static void rotateRight(Node *&to_this);
		static void rotateLeft(Node *&to_this);

		// function to balance our tree.
		static void balance(Node *&to_this);

	public:
		static void printBT(const std::string& prefix, const Search_tree<Type>::Node* node, bool isLeft);
		class Iterator {
			private:
				Search_tree *containing_tree;
				Node *current_node;
				bool is_end;

				// The constructor is private so that only the search tree can create an iterator
				Iterator( Search_tree *tree, Node *starting_node );

			public:
				// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
				Type operator*() const;
				Iterator &operator++();
				Iterator &operator--();
				bool operator==( Iterator const &rhs ) const;
				bool operator!=( Iterator const &rhs ) const;

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
		Iterator find( Type const & );

		void clear();
		bool insert( Type const & );
		bool erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Search_tree<T> const & );
};


//////////////////////////////////////////////////////////////////////
//                Search Tree Private Member Functions               //
//////////////////////////////////////////////////////////////////////
template <typename Type>
void Search_tree<Type>::rotateRight(Node *&to_this) {
	// right rotation
	auto tmp = to_this->left_tree;  // ? why do we use auto
	to_this->left_tree = tmp->right_tree;
	tmp->right_tree = to_this;
	to_this = tmp;
}

template <typename Type>
void Search_tree<Type>::rotateLeft(Node *&to_this) {
	auto tmp = to_this->right_tree;
	to_this->right_tree = tmp->left_tree;
	tmp->left_tree = to_this;
	to_this = tmp;
}

template <typename Type>
void Search_tree<Type>::balance(Node *&to_this) {


	// ! output here
	// std::cout << to_this->node_value << " " << to_this->left_tree->height() << " " << to_this->right_tree->height() <<std::endl;
	// * not strictly necessary since we will always update before calling balance
	to_this->update_height();
	
	// Left heavy
	if (to_this->balanceFactor() < -1) {
		// Case: left-right (double rotation)
		if (to_this->left_tree->balanceFactor() > 0) {
			rotateLeft(to_this->left_tree);
		}

		// we always need to rotate right if left heavy.
		rotateRight(to_this);
	}

	// Right heavy
	else if (to_this->balanceFactor() > 1) {
		// Case: right-left (double rotation)
		if (to_this->right_tree->balanceFactor() < 0){
			rotateRight(to_this->right_tree);
		}

		// we always need to rotate left if right heavy.
		rotateLeft(to_this);
	}

	if (to_this->right_tree) to_this->right_tree->update_height();
	if (to_this->left_tree) to_this->left_tree->update_height();
	to_this->update_height();
}


//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree():
root_node( nullptr ),
tree_size( 0 ),
front_sentinel( new Search_tree::Node( Type() ) ),
back_sentinel( new Search_tree::Node( Type() ) ) {
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
	return ( root_node == nullptr );
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
	if ( empty() ) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator( this, back_sentinel ) : Iterator( this, root_node->front() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator( this, back_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator( this, front_sentinel ) : Iterator( this, root_node->back() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator( this, front_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find( Type const &obj ) {
	if ( empty() ) {
		return Iterator( this, back_sentinel );
	}

	typename Search_tree<Type>::Node *search_result = root_node->find( obj );

	if ( search_result == nullptr ) {
		return Iterator( this, back_sentinel );
	} else {
		return Iterator( this, search_result );
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if ( !empty() ) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
bool Search_tree<Type>::insert( Type const &obj ) {
	if ( empty() ) {
		root_node = new Search_tree::Node( obj );

		// set defaults
		root_node->tree_height = 0;
		tree_size = 1;

		// re-links the sentinels to include this new tree
		front_sentinel->next_node = root_node;
		back_sentinel->previous_node = root_node;
		root_node->previous_node = front_sentinel;
		root_node->next_node = back_sentinel;

		return true;
	} else if ( root_node->insert( obj, root_node ) ) {
		// successful, increment tree size.
		++tree_size;
		return true;
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::erase( Type const &obj ) {
	if ( !empty() && root_node->erase( obj, root_node ) ) {
		// successful, decrement tree size
		--tree_size;
		return true;
	} else {
		return false;
	}
}

// ===========
// Credit for this function goes to Winston Lu 
// ===========
template <typename Type>
void Search_tree<Type>::printBT(const std::string& prefix, const Search_tree<Type>::Node* node, bool isLeft){
    if( node != nullptr ){
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->node_value << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->right_tree, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->left_tree, false);
    }
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node( Type const &obj ):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
next_node( nullptr ),
previous_node( nullptr ),
tree_height( 0 ) {
	// does nothing
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max( left_tree->height(), right_tree->height() ) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::balanceFactor() const {
	return (right_tree ? right_tree->height() + 1 : 0) - (left_tree ? left_tree->height() + 1 : 0);
}
template <typename Type>
int Search_tree<Type>::Node::height() const {
	return ( this == nullptr ) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ( (left_tree == nullptr) && (right_tree == nullptr) );
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	// goes all the way left until it can no longer go left (smallest)
	return ( left_tree == nullptr ) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return ( right_tree == nullptr ) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find( Type const &obj ) {
	if ( obj == node_value ) {
		return this;
	} else if ( obj < node_value ) {
		return (left_tree == nullptr) ? nullptr : left_tree->find( obj );
	} else {
		return ( right_tree == nullptr ) ? nullptr : right_tree->find( obj );
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if ( left_tree != nullptr ) {
		left_tree->clear();
	}

	if ( right_tree != nullptr ) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			left_tree = new Search_tree<Type>::Node( obj );
			left_tree->tree_height = 0; // set tree height to 0 (now contains)
			// inserted on the left side, re-link.
			this->previous_node->next_node = left_tree;
			left_tree->previous_node = previous_node;
			left_tree->next_node = this;
			previous_node = left_tree;

			update_height();

			balance(to_this);

			return true;
		} else {
			if ( left_tree->insert( obj, left_tree ) ) {
				update_height();
				// remember to balance on the way out
				balance(to_this);
				return true;
			} else {
				return false;
			}
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			right_tree = new Search_tree<Type>::Node( obj );
			right_tree->tree_height = 0; // set tree height to 0 (now contains)
			// inserted on the right side, re-link LL
			this->next_node->previous_node = right_tree;
			right_tree->next_node = next_node;
			right_tree->previous_node = this;
			next_node = right_tree;

			update_height();
			balance(to_this); // remember to balance on the way out

			return true;
		} else {
			if ( right_tree->insert( obj, right_tree ) ) {
				update_height();
				balance(to_this);
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			return false;
		} else {
			if ( left_tree->erase( obj, left_tree ) ) {
				update_height();

				if (to_this) {
					balance(to_this);
				}
				return true;
			}

			return false;
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			return false;
		} else {
			if ( right_tree->erase( obj, right_tree ) ) {
				update_height();
				if (to_this) {
					balance(to_this);
				}
				return true;
			}

			return false;
		}
	} else {
		assert( obj == node_value );

		if ( is_leaf() ) {
			// node is a leaf, so delete the node and balance on the way out.
			// re-link LL (ll removal).
			this->previous_node->next_node = this->next_node;
			this->next_node->previous_node = this->previous_node;
			this->next_node = nullptr;
			this->previous_node = nullptr;
			to_this = nullptr;
			delete this;
		} else if ( left_tree == nullptr ) {
			// nothing on the left, only things on the right.

			// take this node out of our linked list
			this->previous_node->next_node = this->next_node;
			this->next_node->previous_node = this->previous_node;

			// point to_this to our next node.
			to_this = right_tree;

			// I don't think balance is necessary here
			// balance(to_this);

			// delete the valued node
			delete this;
		} else if ( right_tree == nullptr ) {
			// nothing on the right, only on the left

			// take this node out of our linked list
			this->previous_node->next_node = this->next_node;
			this->next_node->previous_node = this->previous_node;

			// move to_this to point to our left side subtree
			to_this = left_tree;
			// I don't think balance is necessary here
			// balance(to_this);

			// delete the valued node
			delete this;
		} else {

			// our node value is now the same as the node value of the smallest on the right sub tree (next closest value)
			node_value = right_tree->front()->node_value;

			// erase the smallest node from our right tree.
			right_tree->erase( node_value, right_tree );

			// no re-linking necessary here, since we will have
			// A - B - C - D - E - F
			// A - B - D - D - E - F
			// A - B - D - - - E - F (automatically re-linked on the second erase call)
			update_height();

			// we haven't changed to_this so it should still balance on the way up?
			balance(to_this);
		}

		return true;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator( Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node ):
containing_tree( tree ),
current_node( starting_node ) {
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
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
	// Update the current node to the node containing the next higher value
	// If we are already at end do nothing

	// Your implementation here, do not change the return value
	// not sure if this is correct?
	if (current_node->next_node != nullptr) {
		current_node = current_node->next_node;
	}

	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
	// Update the current node to the node containing the next smaller value
	// If we are already at either rend, do nothing

	// Your implementation here, do not change the return value
	if (current_node->previous_node != nullptr) {
		current_node = current_node->previous_node;
	}
	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node == rhs.current_node );
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node != rhs.current_node );
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Search_tree<T> const &list ) {
	std::cout << "\n ---------------------------------------------------------- \n";
    Search_tree<T>::printBT("", list.root_node, false);    
    return out;
}

#endif
