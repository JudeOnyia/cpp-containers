#include "ra/intrusive_list.hpp"
#include<vector>
#include<iostream>
#include<utility>

namespace ri = ra::intrusive;

struct Widget {
	Widget(int value_) : value(value_) {}
	int value;
	ri::list_hook hook;
};

void print_list(ri::list<Widget, &Widget::hook>& obj){
	for(ri::list<Widget, &Widget::hook>::list_iterator i=(obj.begin()); i!=(obj.end()); ++i){
		std::cout<<(i->value)<<" ";
	}
	std::cout<<std::endl;
}

int main() {
	using std::cout;
	using std::endl;
	using riw = typename ri::list<Widget, &Widget::hook>;
	using itr = typename ri::list<Widget, &Widget::hook>::list_iterator;
	std::vector<Widget> storage;
	for(int i=9; i>=0; --i){
		storage.push_back(Widget(i));
	}
	// Test default constructor
	riw obj_A;
	cout<<(obj_A.size())<<endl;
	// Test insert and begin and end and back
	Widget* wp = storage.data();
	itr ip = obj_A.begin();
	for(int i=0; i<10; ++i){
		obj_A.insert(ip,*wp);
		--ip;
		++wp;
	}
	cout<<(obj_A.size())<<endl;
	cout<<((obj_A.back()).value)<<endl;
	print_list(obj_A);
	// Test move constructor and move assignment
	riw obj_B(std::move(obj_A));
	print_list(obj_B);
	riw obj_C = std::move(obj_B);
	print_list(obj_C);
	// Test clear
	obj_C.clear();
	cout<<(obj_C.size())<<endl;
	print_list(obj_C);

	

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
