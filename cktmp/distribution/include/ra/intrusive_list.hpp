#ifndef INTRUSIVELISTHPP
#define INTRUSIVELISTHPP

#include"parent_from_member.hpp"
#include<utility>

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
			list_hook() : next_(this), prev_(this) {}
			list_hook(const list_hook&) = default;
			list_hook(list_hook&&) = default;
			list_hook& operator=(const list_hook&) = default;
			list_hook& operator=(list_hook&&) = default;
			~list_hook() = default;
			template<class T, list_hook T::* Hook>
			friend class list;
			friend class list_iterator;
		private:
			list_hook* next_;
			list_hook* prev_;
	};

	// Intrusive doubly-linked list (with sentinel node).
	template <class T, list_hook T::* Hook>
	class list {
		public:
			class list_iterator{
				public:
					list_iterator() : ptr_(nullptr) {}
					list_iterator(list_hook* ptrval) : ptr_(ptrval) {}
					list_iterator(T* ptrT) : ptr_(&(ptrT->*hook_ptr)){}
					~list_iterator() = default;
					list_iterator(const list_iterator& other) : ptr_(other.ptr_) {}
					list_iterator& operator=(const list_iterator& other) {
						ptr_ = other.ptr_;
					}
					list_iterator& operator=(list_hook* otherPtr) {
						ptr_ = otherPtr;
					}
					bool operator==(const list_iterator& other) const {
						return (ptr_==(other.ptr_));
					}
					bool operator==(list_hook* otherPtr) const {
						return (ptr_==otherPtr);
					}
					bool operator!=(const list_iterator& other) const {
						return (ptr_!=(other.ptr_));
					}
					bool operator!=(list_hook* otherPtr) const {
						return (ptr_!=otherPtr);
					}
					T* operator->() const {
						T* el_ptr = ra::util::parent_from_member<value_type,list_hook>(ptr_,hook_ptr);
						return el_ptr;
					}
					T& operator*() const{
						T* el_ptr = ra::util::parent_from_member<value_type,list_hook>(ptr_,hook_ptr);
						return (*el_ptr);
					}

					list_iterator operator++(){
						ptr_ = ptr_->next_;
						return *this;
					}
					list_iterator operator++(int){
						list_iterator oldIter(*this);
						ptr_ = ptr_->next_;
						return oldIter;
					}
					list_iterator operator--(){
						ptr_ = ptr_->prev_;
						return *this;
					}
					list_iterator operator--(int){
						list_iterator oldIter(*this);
						ptr_ = ptr_->prev_;
						return oldIter;
					}
					list_hook* getPtr() const { return ptr_; }
				private:
					list_hook* ptr_;
			};

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
			using iterator = list_iterator;
			
			// The non-mutating (bidirectional) iterator type for the list.
			// This type must provide all of the functionality of a
			// bidirectional iterator.
			// The Boost Iterator library may be used to implement this
			// type.
			using const_iterator = const list_iterator;

			// An unsigned integral type used to represent sizes.
			using size_type = std::size_t;

			// Creates an empty list.
			// Time complexity: Constant.
			list() : size_(0) {}

			// Erases any elements from the list and then destroys the list.
			// Time complexity: Either linear or constant.
			~list(){
				clear();
			}

			// Move construction.
			// The elements in the source list (i.e., other) are moved from
			// the source list to the destination list (i.e., *this), preserving
			// their relative order.
			// After the move, the source list is empty.
			// Time complexity: Constant.
			list(list&& other){
				(other.sent_node_.next_)->prev_ = &sent_node_;
				(other.sent_node_.prev_)->next_ = &sent_node_;
				sent_node_.next_ = other.sent_node_.next_;
				sent_node_.prev_ = other.sent_node_.prev_;
				size_ = other.size_;
				other.sent_node_.next_ = &(other.sent_node_);
				other.sent_node_.prev_ = &(other.sent_node_);
				other.size_ = size_type(0);
			}

			// Move assignment.
			// The elements in the source list (i.e., other) are moved from
			// the source list to the destination list (i.e., *this),
			// preserving their relative order.
			// If *this is not empty, *this is cleared before the move operation
			// is applied.
			// After the move, the source list is empty.
			// Precondition: The objects *this and other are distinct.
			// Time complexity: Constant or linear in size of *this.
			list& operator=(list&& other){
				if(size_!=size_type(0)){
					clear();
				}
				(other.sent_node_.next_)->prev_ = &sent_node_;
				(other.sent_node_.prev_)->next_ = &sent_node_;
				sent_node_.next_ = other.sent_node_.next_;
				sent_node_.prev_ = other.sent_node_.prev_;
				size_ = other.size_;
				other.sent_node_.next_ = &(other.sent_node_);
				other.sent_node_.prev_ = &(other.sent_node_);
				other.size_ = size_type(0);
				return *this;
			}

			// Do not allow the copying of lists.
			list(const list&) = delete;
			list& operator=(const list&) = delete;

			// Swaps the elements of *this and x.
			// Swapping the elements of a list with itself has no effect.
			// Time complexity: Constant.
			void swap(list& x){
				list temp(std::move(x));
				x = std::move(*this);
				*this = std::move(temp);
			}

			// Returns the number of elements in the list.
			// Time complexity: Constant.
			size_type size() const { return size_; }

			// Inserts an element in the list before the element referred to
			// by the iterator pos.
			// An iterator that refers to the inserted element is returned.
			// Time complexity: Constant.
			iterator insert(iterator pos, value_type& value){
				if(size_ == size_type(0)){
					sent_node_.next_ = &(value.*hook_ptr);
					sent_node_.prev_ = &(value.*hook_ptr);
					(value.*hook_ptr).next_ = &(sent_node_);
					(value.*hook_ptr).prev_ = &(sent_node_);
				}
				else{
					list_hook* next_hook = pos.getPtr();
					list_hook* current_hook = &(value.*hook_ptr);
					list_hook* prev_hook = next_hook->prev_;
					prev_hook->next_ = current_hook;
					current_hook->prev_ = prev_hook;
					current_hook->next_ = next_hook;
					next_hook->prev_ = current_hook;	
				}
				++size_;
				list_hook* return_hook = &(value.*hook_ptr);
				iterator return_ptr = iterator(return_hook);
				//iterator elmnt_ptr = ra::util::parent_from_member<value_type,list_hook>(current_hook,hook_ptr);
				return return_ptr;
			}

			// Erases the element in the list at the position specified by the
			// iterator pos.
			// An iterator that refers to element following the erased element
			// is returned if such an element exists; otherwise, end() is
			// returned.
			// Time complexity: Constant.
			iterator erase(iterator pos){
				if(size_ == size_type(0)){
					return end();
				}
				else{
					list_hook* current_hook = pos.getPtr();
					list_hook* prev_hook = current_hook->prev_;
					list_hook* next_hook = current_hook->next_;
					prev_hook->next_ = next_hook;
					next_hook->prev_ = prev_hook;
					current_hook->prev_ = current_hook;
					current_hook->next_ = current_hook;
					--size_;
					return (iterator(next_hook));
				}
			}

			// Inserts the element with the value x at the end of the list.
			// Time complexity: Constant.
			void push_back(value_type& x){
				iterator res = insert(end(),x);
			}

			// Erases the last element in the list.
			// Precondition: The list is not empty.
			// Time complexity: Constant.
			void pop_back(){
				iterator last = --(end());
				iterator res = erase(last);
			}

			// Returns a reference to the last element in the list.
			// Precondition: The list is not empty.
			// Time complexity: Constant.
			reference back(){
				list_hook* last_hook = sent_node_.prev_;
				value_type* last_element = ra::util::parent_from_member<value_type,list_hook>(last_hook,hook_ptr);
				return (*last_element);
			}
			const_reference back() const{
				const list_hook* last_hook = sent_node_.prev_;
				const value_type* last_element = ra::util::parent_from_member<value_type,list_hook>(last_hook,hook_ptr);
				return (*last_element);
			}

			// Erases any elements from the list, yielding an empty list.
			// Time complexity: Either linear or constant.
			void clear(){
				/*list_hook* current_hook = (sent_node_.prev_)->next_;
				list_hook* next_hook;
				for(size_type i=0; i<=size_; ++i){
					next_hook = current_hook->next_;
					current_hook->next_ = current_hook;
					current_hook->prev_ = current_hook;
					current_hook = next_hook;
				}
				*/
				list_hook* itslf = (sent_node_.prev_)->next_;
				sent_node_.prev_ = itslf;
				sent_node_.next_ = itslf;
				size_ = size_type(0);
			}

			// Returns an iterator referring to the first element in the list
			// if the list is not empty and end() otherwise.
			// Time complexity: Constant.
			const_iterator begin() const{
				if(size_ == size_type(0)){
					return end();
				}
				else{
					const_iterator first_hook = sent_node_.next_;
					return first_hook;
				}
			}

			iterator begin(){
				if(size_ == size_type(0)){
					return end();
				}
				else{
					iterator first_hook = sent_node_.next_;
					return first_hook;
				}
			}

			// Returns an iterator referring to the fictitious one-past-the-end
			// element.
			// Time complexity: Constant.
			const_iterator end() const {
			       /*const iterator last_element = ra::util::parent_from_member<value_type,list_hook>(last_hook,hook_ptr);
			       const iterator end_element = last_element + 1;
			       return end_element;*/
			       return &sent_node_;	
			}
			iterator end() {
				/*list_hook* last_hook = sent_node_.prev_;
				iterator last_element = ra::util::parent_from_member<value_type,list_hook>(last_hook,hook_ptr);
				iterator end_element = last_element + 1;
				return end_element;
				*/
				return &sent_node_;
			}

		private:
			list_hook sent_node_;
			std::size_t size_;

	};

}
#endif
