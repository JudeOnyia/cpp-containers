#include <iostream>
#include <type_traits>
#include <functional>
#include <cstdint>
#include <utility>
#include <ra/sv_set.hpp>
#include <iterator>
#include <forward_list>

namespace ri = ra::container;

template <class T, class C>
void test()
{
	using sv_set = ri::sv_set<T, C>;
	static_assert(std::is_same_v<typename sv_set::value_type, T>);
	static_assert(std::is_same_v<typename sv_set::key_type, T>);
	static_assert(std::is_same_v<typename sv_set::key_compare, C>);
	static_assert(std::is_same_v<typename sv_set::size_type, std::size_t>);
	static_assert(std::is_same_v<typename std::iterator_traits<
	  typename sv_set::iterator>::iterator_category,
	  std::random_access_iterator_tag>);
	static_assert(std::is_same_v<typename std::iterator_traits<
	  typename sv_set::const_iterator>::iterator_category,
	  std::random_access_iterator_tag>);
	//sizeof(typename sv_set::iterator);
	//sizeof(typename sv_set::const_iterator);
	static_assert(std::is_class_v<typename sv_set::ordered_and_unique_range>);

	static_assert(std::is_same_v<typename std::pair<
	  typename sv_set::iterator, bool>, decltype(
	  std::declval<sv_set>().insert(T(0)))>);

	{
		const sv_set a;
		sv_set x(a);
		sv_set y(std::move(x));
		x = y;
		x = std::move(y);
	}

	{
		const T data[3] = {T(1), T(2), T(3)};
		const sv_set a;
		sv_set b;
		sv_set c;
		sv_set d(typename sv_set::ordered_and_unique_range(), std::begin(data), std::end(data) - std::begin(data));
		a.begin();
		a.end();
		a.size();
		a.capacity();
		b.reserve(1000);
		b.shrink_to_fit();
		b.insert(T(42));
		b.erase(typename sv_set::const_iterator());
		c.swap(b);
		b.clear();
		a.find(T(42));
		C k = a.key_comp();
	}

	{
		const std::forward_list<T> s{T(1), T(2), T(3)};
		const sv_set a(typename sv_set::ordered_and_unique_range(),
		  s.cbegin(), 3);
	}

}

int main()
{
	test<char, std::less<char>>();
	test<int, std::greater<int>>();
	test<double, std::less<double>>();
	test<std::vector<int>, std::greater<std::vector<int>>>();
}
