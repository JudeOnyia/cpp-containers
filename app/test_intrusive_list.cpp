#include "ra/intrusive_list.hpp"
#include<vector>
#include<iostream>

namespace ri = ra::intrusive;

struct Widget {
	Widget(int value_) : value(value_) {}
	int value;
	ri::list_hook hook;
};

int main() {
	using std::cout;
	using std::endl;
	using riw = typename ri::list<Widget, &Widget::hook>;
	using itr = typename ri::list<Widget, &Widget::hook>::list_iterator;
	std::vector<Widget> storage;
	for(int i=0; i<10; ++i){
		storage.push_back(Widget(i));
	}
	// Test default constructor
	riw obj_A;
	cout<<(obj_A.size())<<endl;
	// Test insert and begin
	Widget* wp = storage.data();
	itr ip = obj_A.begin();
	for(int i=0; i<10; ++i){
		obj_A.insert(ip,*wp);
		--ip;
		++wp;
	}
	cout<<(obj_A.size())<<endl;
	//itr iz = obj_A.begin();
	for(itr i=(--(obj_A.end())); i!=(obj_A.end()); --i){
		cout<<(i->value)<<" ";
	}
	cout<<endl;
	

	/*
	std::vector<Widget> storage;
	storage.push_back(Widget(42));
	ri::list<Widget, &Widget::hook> values;
	for (auto&& i : storage) {
		values.push_back(i);
	}
	values.clear();
	*/
}
