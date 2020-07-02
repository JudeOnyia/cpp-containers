#ifndef INTRUSIVELISTHPP
#define INTRUSIVELISTHPP

namespace ra::intrusive {

	// Per-node list management information class.
	// The implementation-defined type that contains per-node list
	// management information (i.e., successor and predecessor).
	// This class has the list class template as a friend.
	// This type must contain pointers (of type list_hook*) to the
	// next and previous node in the list.
	class list_hook {
		public:
			// The only allowable public members for this class
			// are the ones listed below.
			// The particular behavior of the following special
			// member functions are implementation defined and
			// may be defaulted if appropriate.
			list_hook();
			list_hook(const list_hook&);
			list_hook(list_hook&&);
			list_hook& operator=(const list_hook&);
			list_hook& operator=(list_hook&&);
			˜list_hook();
	};

	// Intrusive doubly-linked list (with sentinel node).
	template <class T, list_hook T::* Hook>
	class list {
		public:

			// The type of the elements in the list.
			using value_type = T;

			// The pointer-to-member associated with the list hook object.
			static constexpr list_hook T::* hook_ptr = Hook;

			// The type of a mutating reference to a node in the list.
			using reference = T&;

			// The type of a non-mutating reference to a node in the list.
			using const_reference = const T&;

			// The mutating (bidirectional) iterator type for the list.
			// This type must provide all of the functionality of a
			// bidirectional iterator.
			// The Boost Iterator library may be used to implement this
			// type.
			using iterator = implementation-defined;
			
			// The non-mutating (bidirectional) iterator type for the list.
			// This type must provide all of the functionality of a
			// bidirectional iterator.
			// The Boost Iterator library may be used to implement this
			// type.
			using const_iterator = implementation-defined;

			// An unsigned integral type used to represent sizes.
			using size_type = std::size_t;

			// Creates an empty list.
			// Time complexity: Constant.
			list();

			// Erases any elements from the list and then destroys the list.
			// Time complexity: Either linear or constant.
			˜list();

			// Move construction.
			// The elements in the source list (i.e., other) are moved from
			// the source list to the destination list (i.e., *this), preserving
			// their relative order.
			// After the move, the source list is empty.
			// Time complexity: Constant.
			list(list&& other);

			// Move assignment.
			// The elements in the source list (i.e., other) are moved from
			// the source list to the destination list (i.e., *this),
			// preserving their relative order.
			// If *this is not empty, *this is cleared before the move operation
			// is applied.
			// After the move, the source list is empty.
			// Precondition: The objects *this and other are distinct.
			// Time complexity: Constant or linear in size of *this.
			list& operator=(list&& other);

			// Do not allow the copying of lists.
			list(const list&) = delete;
			list& operator=(const list&) = delete;

			// Swaps the elements of *this and x.
			// Swapping the elements of a list with itself has no effect.
			// Time complexity: Constant.
			void swap(list& x);

			// Returns the number of elements in the list.
			// Time complexity: Constant.
			size_type size() const;

			// Inserts an element in the list before the element referred to
			// by the iterator pos.
			// An iterator that refers to the inserted element is returned.
			// Time complexity: Constant.
			iterator insert(iterator pos, value_type& value);

			// Erases the element in the list at the position specified by the
			// iterator pos.
			// An iterator that refers to element following the erased element
			// is returned if such an element exists; otherwise, end() is
			// returned.
			// Time complexity: Constant.
			iterator erase(iterator pos);

			// Inserts the element with the value x at the end of the list.
			// Time complexity: Constant.
			void push_back(value_type& x);

			// Erases the last element in the list.
			// Precondition: The list is not empty.
			// Time complexity: Constant.
			void pop_back();

			// Returns a reference to the last element in the list.
			// Precondition: The list is not empty.
			// Time complexity: Constant.
			reference back();
			const_reference back() const;

			// Erases any elements from the list, yielding an empty list.
			// Time complexity: Either linear or constant.
			void clear();

			// Returns an iterator referring to the first element in the list
			// if the list is not empty and end() otherwise.
			// Time complexity: Constant.
			const_iterator begin() const;
			iterator begin();

			// Returns an iterator referring to the fictitious one-past-the-end
			// element.
			// Time complexity: Constant.
			const_iterator end() const;
			iterator end();

	};

}
#endif