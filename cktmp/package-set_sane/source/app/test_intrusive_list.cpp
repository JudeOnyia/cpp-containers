#include <iostream>
#include <type_traits>
#include <ra/intrusive_list.hpp>
#include <iterator>

namespace ri = ra::intrusive;

/*

NOTE:

These tests assume that the test class has a public member called data_member.

*/

struct Widget {
	Widget(int value_) : value(value_) {}
	int value;
	ri::list_hook hook;
	int data_member;
};

struct Gadget {
	Gadget(int) {}
	Gadget(const Gadget&) = delete;
	Gadget& operator=(const Gadget&) = delete;
	Gadget(Gadget&&) = delete;
	Gadget& operator=(Gadget&&) = delete;
	//std::mutex m;
	int value;
	ri::list_hook hook;
	int data_member;
};

// test assumes that T can be constructed from int
template <class T>
void test()
{
	using list_hook = ri::list_hook;
	using list = typename ri::list<T, &T::hook>;

	static_assert(std::is_class_v<list>);
	static_assert(std::is_class_v<list_hook>);
	static_assert(std::is_same_v<typename list::value_type, T>);
	static_assert(list::hook_ptr == &T::hook);
	static_assert(std::is_same_v<typename list::reference, T&>);
	static_assert(std::is_same_v<typename list::const_reference, const T&>);
	static_assert(std::is_class_v<typename list::iterator>);
	static_assert(std::is_class_v<typename list::const_iterator>);
	static_assert(std::is_same_v<typename list::size_type, std::size_t>);
	static_assert(std::is_same_v<typename std::iterator_traits<
	  typename list::iterator>::iterator_category,
	  std::bidirectional_iterator_tag>);
	static_assert(std::is_same_v<typename std::iterator_traits<
	  typename list::const_iterator>::iterator_category,
	  std::bidirectional_iterator_tag>);

	static_assert(std::is_convertible_v<typename list::iterator,
	  typename list::const_iterator>);

	// move assign
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>() =
	  std::declval<typename list::iterator>()),
	  typename list::iterator&>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>() =
	  std::declval<typename list::const_iterator>()),
	  typename list::const_iterator&>);

	static_assert(std::is_same_v<decltype(
	  *std::declval<typename list::iterator>()), T&>);
	static_assert(std::is_same_v<decltype(
	  *std::declval<typename list::const_iterator>()), const T&>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>().operator->()), T*>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>().operator->()), const T*>);

	static_assert(std::is_same_v<decltype(
	  ++std::declval<typename list::iterator>()), typename list::iterator&>);
	static_assert(std::is_same_v<decltype(
	  ++std::declval<typename list::const_iterator>()),
	  typename list::const_iterator&>);

//	static_assert(std::is_same_v<decltype(
//	  std::declval<typename list::iterator>()++), typename list::iterator>);
//	static_assert(std::is_same_v<decltype(
//	  std::declval<typename list::const_iterator>()++),
//	  typename list::const_iterator>);

	static_assert(std::is_same_v<decltype(
	  --std::declval<typename list::iterator>()), typename list::iterator&>);
	static_assert(std::is_same_v<decltype(
	  --std::declval<typename list::const_iterator>()),
	  typename list::const_iterator&>);

//	static_assert(std::is_same_v<decltype(
//	  std::declval<typename list::iterator>()--), typename list::iterator&>);
//	static_assert(std::is_same_v<decltype(
//	  std::declval<typename list::const_iterator>()--),
//	  typename list::const_iterator&>);

	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>()--), typename list::iterator>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>()--),
	  typename list::const_iterator>);

	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>() ==
	  std::declval<typename list::iterator>()),
	  bool>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>() ==
	  std::declval<typename list::const_iterator>()),
	  bool>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>() ==
	  std::declval<typename list::const_iterator>()),
	  bool>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>() ==
	  std::declval<typename list::iterator>()),
	  bool>);

	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>() !=
	  std::declval<typename list::iterator>()),
	  bool>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>() !=
	  std::declval<typename list::const_iterator>()),
	  bool>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::iterator>() !=
	  std::declval<typename list::const_iterator>()),
	  bool>);
	static_assert(std::is_same_v<decltype(
	  std::declval<typename list::const_iterator>() !=
	  std::declval<typename list::iterator>()),
	  bool>);

	{
		const list a;
		list b;
		list c(std::move(b));
		b = std::move(c);
	}

	T e0(42);
	T e1(42);
	{
		const list a;
		list b;
		list c;
		b.swap(c);
		a.size();
		b.insert(b.begin(), e0);
		b.erase(b.begin());
		b.push_back(e1);
		b.pop_back();
		a.back();
		b.clear();
		a.begin();
		a.end();
	}

	{
		const list cl;
		list l;
		typename list::const_iterator ci = cl.begin();
		typename list::iterator i = l.begin();
		++ci;
		++i;
		--ci;
		--i;
		*ci;
		*i;
		ci = cl.end();
		i = l.end();

#if 0
		// The following should not work:
		i = ci;
#endif
		{
//			ra::intrusive::list<const Widget,
//			  const_cast<const list_hook Widget::*>(&Widget::hook)> z;
			const typename list::iterator c_i = l.end();
			const typename list::const_iterator c_ci = cl.end();
		}

		i->data_member;
		ci->data_member;

		ci == i;
		i == ci;
		i == i;
		ci == ci;

		ci != i;
		i != ci;
		i != i;
		ci != ci;
	}
}

int main()
{
	test<Widget>();
	test<Gadget>();
}
