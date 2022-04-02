/*****************************************
 * UW User ID:  a26luo
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2022
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

// REMINDER: try to use the functions to access next/previous (in case they were private).
// should also try to use begin/end/rbegin/rend...... forgot they existed... :( 

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here : creates empty list (only two sentinel nodes)


	// create two head/tail sentinel nodes
	this->list_head = new Double_node;
	this->list_tail = new Double_node;

	// set list_size
	this->list_size = 0;

	// set the next of the head and the previous of the tail. Hardcoded (clearer) but could be replaced with rend and end.
	this->list_head->next_node = list_tail;
	this->list_tail->previous_node = list_head;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here - Copies values of list into our new list!

	// creating the nodes
	this->list_head = new Double_node;
	this->list_tail = new Double_node;
	this->list_head->next_node = list_tail;
	this->list_tail->previous_node = list_head;

	this->list_size = list.list_size; // set list size equal to each other

	Double_node temp = *list.begin(); // set temp to be the first element.

	while(temp.next() != nullptr) {
		// while our next is not a nullptr
		this->push_back(temp.value()); // add a node to the end with the value of the original list. Works even on sentinel nodes.
	}

	// no need to deallocate temp since it isn't creating anything dynamically
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// Enter your implementation here : deletes the list node by node. Deallocates EVERYTHING (all memory freed).
	// can do this recursively, or by keeping next pointer.
	Double_node * head = this->list_head;
	while(head->next_node != nullptr) {
		// go through every element until the last one
		Double_node * temp = head; // stores our node as a temporary node
		head = head->next_node; // sets head to next node!
		delete temp; // deletes the node
		temp = nullptr;
	}
	delete head; // deletes the last node (would be the sentinel tail)
	head = nullptr; // set the head to be nullptr (not strictly necessary since it only exists within the scope of this function).
}


template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// Enter your implementation here
	return this->list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Enter your implementation here - Checks if the list is empty
	if (this->size() == 0){
		// size is zero, so list is empty. Return True
		return true;
	} else {
		// size is NOT zero, so list is NOT empty. Return False
		return false;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Enter your implementation here - returns what exists at the value of the front
	if(this->size() == 0) {
		// list is empty, so it is not possible to get the front. Throws underflow error.
		throw underflow();
	} else {
		// returns value of node after head sentinel node.
		return this->list_head->next()->value();
	}
	return Type(); // This returns a default value of Type !! Code should never get here
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Enter your implementation here - returns what exists at the value of the back
	if(this->size() == 0) {
		// list is empty, so it is not possible to get the back. Throws underflow error.
		throw underflow();
	} else {
		return this->list_tail->previous()->value(); // get the value at the node before our tail sentinel node.
	}
	return Type(); // This returns a default value of Type !! code should never get here
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Enter your implementation here - Should get the address of the first node
	return this->list_head->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Enter your implementation here - Return address of tail sentinel
	return this->list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Enter your implementation here - Return address of last node (not the sentinel)
	return this->list_tail->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Enter your implementation here - Return the address of the head sentinel
	return this->list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Enter your implementation here - Return addr of node with value equal. Else return end()
	Double_node * stepper = this->list_head;
	while(stepper->next() != nullptr) {
		// there are still more nodes in the list
		if (stepper->value() == obj) { // check value == obj
			return stepper; // if matches, we return the stepper. This function will exit here
		}
		stepper = stepper->next(); // otherwise, continue incrementing the stepper.
	}
	return this->end(); // returns end() if we have not found a match. Could also return something to do with stepper, or this->list_tail, etc.
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here - Return num of list with same val as obj.
	int count = 0; // counter starts at 0
	Double_node * stepper = this->list_head; // similar stepper to find
	while(stepper->next() != nullptr) {
		// there are still more nodes in the list
		if (stepper->value() == obj) { // check value == obj
			count += 1; // if matches, we increment the count
		}
		stepper = stepper->next(); // always increment the stepper
	}
	return count; // returns our counter with matches. Will return 0 since count will not have been incremented if no matches were found.
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// Enter your implementation here - Add node at the front of the list.
	Double_node * new_node = new Double_node(obj, this->list_head, this->list_head->next_node); // create new node with value of obj, head node previous, first node next)
	// in this state, we have (temporarily) two nodes pointing to begin().

	// now we point our first node next to the new node, and the new node has already been pointed to go to the original older first node.
	this->list_head->next_node->previous_node = new_node;// point previous of original head to our new node
	this->list_head->next_node = new_node; // point next of head to our node.
	

	this->list_size += 1; // since we have added a node, our list size must now increase.
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// Enter your implementation here - Add node to the back of the list
	// very similar to push_front with some small changes.
	
	Double_node * new_node = new Double_node(obj, this->list_tail->previous_node, this->list_tail); // create new node with value of obj, last node previous, tail node next)
	// in this state, we have two nodes (temporarily) pointing to our tail sentinel.

	// now we point our last node next to the new node, and the new node has already been pointed to go to the tail sentinel
	this->list_tail->previous_node->next_node = new_node; // set original last node's next node to new_node (added into list)
	this->list_tail->previous_node = new_node; // set tail sentinel previous to our node

	this->list_size += 1; // since we have added a node, our list size must now increase.
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() { // if I could, I would make pop_* functions return the value of the deleted node
	// Enter your implementation here - remove first node in place.
	if (this->size() == 0) {
		// if the list is empty, throw an underflow
		throw underflow();
	}
	// else continue
	Double_node * temp = this->begin(); // our temp node is now the node that we need to replace.
	this->list_head->next_node = temp->next(); // next node for our sentinel gets set to the original second node.
	this->begin()->previous_node = this->list_head; // previous node for our original second node gets pointed to head sentinel.

	this->list_size -= 1; // since we have removed a node, our list size must now decrease.

	delete temp; // delete our node to be pop'd
	temp = nullptr; // once again not sure why this is done but ECE 150 says it is not necessary but suggested.
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() { // if I could, I would make pop_* functions return the value of the deleted node
	// Enter your implementation here - remove last node in place.
	// very similar to pop_front() but with same nuances as push_back()
	if (this->size() == 0) {
		// if the list is empty, throw an underflow
		throw underflow();
	}
	Double_node * temp = this->rbegin(); // create a temporary node (the one that we will delete)
	this->end()->previous_node = temp->previous_node; // point tail sentinel to the node preceding one to be deleted.
	this->rbegin()->next_node = this->list_tail; // point the node preceding one to be deleted to tail node explicitly.

	this->list_size -= 1; // since we have removed a node, our list size must now decrease.

	delete temp; // deleting the node now
	temp = nullptr; // set to nullptr
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here - deletes all nodes with value equal to obj.

	// similar to count(), so we take that code and change it a bit.

	int count = 0; // counter starts at 0
	Double_node * stepper = this->list_head; // similar stepper to find
	while(stepper->next() != nullptr) {
		// there is still more to go through
		if (stepper->value() == obj) { // check value == obj
			count += 1; // if matches, we increment the count
			this->list_size -= 1; // if we have a match, then our list size should decrement (since we delete the node)

			Double_node * temp = stepper;

			Double_node * prev_node = stepper->previous();
			// now instead of only counting, we have to delete the node!

			stepper = stepper->next(); // incrementing stepper

			// if we have original and then stepper,
			// original->previous->next = stepper
			// stepper->previous = original->previous
			prev_node->next_node = stepper; // the previous nodes next node will now be set to stepper (skipping temp) 
			stepper->previous_node = prev_node; // the steppers previous node is now set to previous (skipping temp)

			delete temp; // deletes the temporary node;
			temp = nullptr; // sets to nullptr
		} else {
			// increments the stepper if it has not been done already.
			// in our re-linking, we have already incremented the stepper! (hence we are inside the else loop)
			stepper = stepper->next();
		}
		
	}
	return count; // return count of equal nodes.
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here 
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	// Enter your implementation here - create a node with nv, pn, nn
	this->node_value = nv; // node value = node value
	this->previous_node = pn; // previous node = previous node
	this->next_node = nn; // next node = next node
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return this->node_value;
	// return Type(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return this->previous_node;
	// return nullptr;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return this->next_node;
	// return nullptr;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
