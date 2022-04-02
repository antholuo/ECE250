/*****************************************
 * UW User ID:  a26luo
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2022
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();


	private:
		// Your member variables
		Type * d_array;
		int d_size; 	// deque size
		int d_cap; 		// deque capacity
		int w_f; 		// deque front write index
		int w_r;		// deque rear write index
		int initial_cap;// initial capacity

		// Any private member functions
		//   - helper functions for resizing your array?

		void double_array();	// function to double array
		void halve_array();		// function to halve array
		int mod(int num, int size) const;	// custom modulo function (since I can't overload %?)

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
// Your initalization list
{
	// Enter your implementation here

	// Takes argument n as initial capacity of the underlying array for the deque.
	// if n< 16, set array to be 16.

	// check if n < 16
	if (n < 16) {
		n = 16; // sets n to be 16 if it is less than 16.
	}

	d_array = new Type[n]; 	// sets our pointer deque_array to a new array of size 16 or n.
	d_size = 0;				// sets initial size to be 0
	d_cap = n;				// sets current capacity to be equal to n
	initial_cap = n;		// sets initial capacity to be equal to n
	
	// front and rear write position denoted by w_f and w_r
	// Note: (use % d_cap to get pointer position when adding or subtracting).
	w_f = 0;
	w_r = 1; 
	// not going to start at the same location, is going to be ok because will be written to that point regardless.
	// eventually, if w_f wraps to be equal to w_r, then size = cap and so we will increase and reset w_f and w_r

}

// Copy Constructor (OPTIONAL)
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	// Enter your implementation here

	// essentially copying over member variables
	d_size = deque.d_size;
	d_cap = deque.d_cap;
	initial_cap = deque.initial_cap;
	w_f = deque.w_f;
	w_r = deque.w_r;


	// create new array with same size as deque array.
	d_array = new Type[deque.capacity()];

	for(int i = 0; i < d_cap; i++) {
		// we can blindly copy every element.
		// this may not be as fast as copying only elemetns between front and back, but it will work in O(n) time.
		// it is also simpler so ... less likely to break?
		d_array[i] = deque.d_array[i];
	}
}

// Move Constructor (OPTIONAL)
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	// Enter your implementation here
	d_size = 0;
	d_cap = 16; // d_cap and initial_cap = 16 since we are creating empty.
	initial_cap = 16;
	d_array = new Type[initial_cap];
	w_f = 0;
	w_r = 1;

	swap(deque); // swap with existing 	deque
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
	// - deconstructor for deque, deletes all dynamically allocated memory.

	delete[] d_array; // deletes the entire array
	d_array = nullptr;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here - returns the size of the deque
	return d_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here - returns the capacity of the deque
	return d_cap;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here - returns true if empty, false otherwise
	if (d_size == 0) {
		return true;
	}
	return false;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here - returns what is at the front of the deque
	if (empty()) {
		// our deque is empty so there is nothing at the front. Throw underflow.
		throw underflow();
	} else {
		// return element at the front (remember that we have to shift the write index to get the element index).
		return d_array[ mod((w_f + 1), d_cap) ]; 
	}
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here - returns what is at the back of the deque
	if (empty()) {
		// deque is empty, throw underflow.
		throw underflow();
	} else {
		// return element at the rear (remember to shift write index to get element index).
		return d_array[mod((w_r - 1), d_cap)];
	}
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );

	// Enter your implementation here
	
	// TODO: used std::swap();

	std::swap(this->d_cap, deque.d_cap);
	std::swap(this->d_size, deque.d_size);
	std::swap(this->initial_cap, deque.initial_cap);
	std::swap(this->w_f, deque.w_f);
	std::swap(this->w_r, deque.w_r);

	// iirc std::swap swaps array elements not arrays themselves?
	Type * temp_p;
	temp_p = this->d_array;
	this->d_array = deque.d_array;
	deque.d_array = temp_p;

	// no dangle, no clear memory since contents are still being used.
	temp_p = nullptr;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	// Pushes element to front of deque. 
	// if deque is full, double the capacity of the deque.

	if (d_size == d_cap) {
		// if we are at size limit, double the array
		double_array();
	}

	// then, push_front as we would regularly (no need to worry about sizing issues)
	d_array[w_f] = obj;				// set corresponding index (recall w_f is write index) to new object
	w_f = mod((w_f - 1), d_cap); 	// move w_f for next time (once again, maintaining that w_f is always good-to-write)
	d_size += 1; 					// increase size
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	if (d_size == d_cap) {
		// if we are at size limit, double the array
		double_array();
	}

	// then, push_back as we would regularly (no need to worry about sizing issues)
	d_array[w_r] = obj;				// set corresponding index to new object
	w_r = mod((w_r + 1), d_cap); 	// increase the w_r for next time (w_r is always good-to-write)
	d_size += 1;					// increase size of deque
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here - remove front element.
	// if size is 1/4 capacity or less after pop, then halve the size of the deque. (never smaller than 16)

	// interesting is that we don't need to delete the objec itself since it will just be overwritten when we pop again?
	if(empty()) {
		throw underflow(); // queue is empty, so throw an underflow
	} else {
		// not empty
		w_f = mod((w_f + 1), d_cap); // move our write index back.
	}

	d_size -= 1; // decrement size

	// check if we need to resize the array.
	if (d_cap >= 32) {
		// it is possible to even consider resizing if our capacity is larger than 16

		// NOTE: in this design, we wil only have 2^n sized arrays, so checking for 16 is the same as functionally checking for >=32.
		// that is to say, d_cap > 16 == d_cap >= 32 in ALL possible cases.
		// in this instance, we put the work of verifying size on the caller, but !
		// some implementations could have halve_array determine whether or not changing the size is possible. (may be better)

		if (d_size * 4 <= d_cap) {
			// from the spec, if 1/4 full or LESS, halve the array.
			halve_array();
		}
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
	// if size is 1/4 capacity or less after pop, then halve the size of the deque. (never smaller than 16)

	// once again, no need to delete value, just move w_r
	if(empty()) {
		throw underflow(); // queue is empty, so throw an underflow
	} else {
		// not empty
		w_r = mod((w_r - 1), d_cap);
	}

	d_size -= 1; // decrement size

	// following portion is identical to pop_front in terms of checking for minimum size requiremetns before re-sizing.
	if (d_cap >= 32) {
		// it is possible to even consider resizing
		if (d_size * 4 <= d_cap) {
			// from the spec, if 1/4 full or LESS, halve the array.
			halve_array();
		}
	}
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here

	// could also use swap! 
	delete [] d_array;
	d_array = new Type[initial_cap];
	d_size = 0;
	w_f = 0;
	w_r = 1;
	d_cap = initial_cap;

}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functions (helper functions) here
template <typename Type>
void Resizable_deque<Type>::double_array() {
	// doubles the size of the array, copying all the data over.
	// remember, our array is front -> back

	Type * temp_arr = new Type[d_cap * 2]; // new array with double the capacity.

	int old_idx = mod((w_f+1), d_cap); // set our index to the front element. We will start moving this to the right until we reach d_r.
	int new_idx = 0;
	while(new_idx < d_size) { // while we cycle through all elements of the old (full) array
		temp_arr[new_idx] = d_array[old_idx];
		new_idx += 1; // should never have any issues incrementing this one (newcap =)

		old_idx = mod((old_idx + 1), d_cap); // increment old_idx all the way around.
	}

	delete[] d_array; // delete the old array (now that values are transferred)
	d_array = temp_arr; // relink pointer to new array.
	temp_arr = nullptr; // no dangle

	d_cap = d_cap * 2; // double the cap
	w_f = d_cap - 1; // w_f is at the very end
	w_r = new_idx; // should give an easy way to track our final index used == w_r;
	// size is still unchanged.
}

template <typename Type>
void Resizable_deque<Type>::halve_array() {
	// halves the size of the array, copying all the data over.

	// NOTE: we intentionally choose to leave the work of checking whether or not our array is valid on the parent (caller) function.
	// this is because we want the halve_array() function to distinctly mirror what double_array does. That is,
	// halve_array will ALWAYS halve the array, and should predictably halve the array no matter what.
	// The caller should determine when it is appropriate to use this function.

	int old_cap = d_cap; // keep track of the old capacity (needed when we mod)
	d_cap /= 2; // update the new capacity
	Type * temp_arr = new Type[old_cap];
	int old_idx = mod((w_f+1), old_cap); // set our index to front element. move this until we reach rear index
	int new_idx = 0;
	while(new_idx < (d_size)) { // iterate through all the elements (array is circular, so just make sure to increment all existing elem)
		temp_arr[new_idx] = d_array[old_idx];
		new_idx += 1; // should never run into issues with going out of bounds (size should be 1/2 capacity new)

		old_idx = mod((old_idx + 1), old_cap); // increment old_idx all the way around
	}

	// everything copied. Process same as double.
	delete[] d_array;
	d_array = temp_arr;
	temp_arr = nullptr;

	// d_cap already set.
	w_f = d_cap -1; // w_f at the very end;
	w_r = new_idx; // w_r at the very end of the index (indexed from 1, so we will be offset to write to the next open spot)
	// size is still unchanged.
}

template <typename Type>
int Resizable_deque<Type>::mod(int num, int size) const {
	// deals with negatives in modulo (instead of just writing (num + d_size) % d_size)
	
	// CONSIDER: could probably make this only work on num, and take this->d_size..

	return (num + size) % size;
    // return (num % size + size) %size;
}


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "capacity: ";
	out << list.capacity();
	out << " | size: ";
	out << list.size();
	out << " | front: ";
	out << list.w_f;
	out << " | rear: ";
	out << list.w_r;
	out << "\n";
	out << "printing all \n";
	for(int i = 0; i < list.d_cap; i++) {
		out << "-- ";
		out << i;
		out << "	";
		out << list.d_array[i];
		if (i == list.w_f) {
			out << "	<== FRONT";
		}
		if (i == list.w_r) {
			out << "	<==REAR";
		}
		out << "\n";
		
	}
	return out;
}

#endif
