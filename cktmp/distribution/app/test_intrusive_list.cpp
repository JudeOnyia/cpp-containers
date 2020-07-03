#include "ra/intrusive_list.hpp"
#include<vector>
#include<iostream>
#include<utility>

namespace ri = ra::intrusive;

struct Widget {
	Widget(int value_) : value(value_) {}
	int value;
	ri::list_hook hook;
	ri::list_hook hook2;
};

void print_list(ri::list<Widget, &Widget::hook>& obj){
	for(ri::list<Widget, &Widget::hook>::list_iterator i=(obj.begin()); i!=(obj.end()); ++i){
		std::cout<<(i->value)<<" ";
	}
	std::cout<<std::endl;
}

void print_list2(ri::list<Widget, &Widget::hook2>& obj){
	for(ri::list<Widget, &Widget::hook2>::list_iterator i=(obj.begin()); i!=(obj.end()); ++i){
		std::cout<<(i->value)<<" ";
	}
	std::cout<<std::endl;
}

/*void make_list(int low, int high, std::vector<Widget>& storage, ri::list<Widget, &Widget::hook>& obj){
       for(int i=high; i>=low; --i){
	       storage.push_back(Widget(i));
       }
       Widget* wp = storage.data();
       ri::list<Widget, &Widget::hook>::list_iterator ip = obj.begin();
       for(int i=0; i<(storage.size()); ++i){
	       obj.insert(ip,*wp);
	       --ip;
	       ++wp;
       }
}*/	       

int main() {
	using std::cout;
	using std::endl;
	using riw = typename ri::list<Widget, &Widget::hook>;
	using riw2 = typename ri::list<Widget, &Widget::hook2>;
	using itr = typename ri::list<Widget, &Widget::hook>::list_iterator;
	using itr2 = typename ri::list<Widget, &Widget::hook2>::list_iterator;
	std::vector<Widget> storage;
	for(int i=9; i>=0; --i){
		storage.push_back(Widget(i));
	}
	// Test default constructor
	riw obj_A;
	riw2 obj_AA;
	cout<<(obj_A.size())<<endl;
	// Test insert and begin and end and back
	Widget* wp = storage.data();
	itr ip = obj_A.begin();
	itr2 ip2 = obj_AA.begin();
	for(int i=0; i<10; ++i){
		obj_A.insert(ip,*wp);
		obj_AA.insert(ip2,*wp);
		--ip;
		--ip2;
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
	// Test erase
	print_list2(obj_AA);
	obj_AA.erase(obj_AA.begin());
	Widget* bk = &(obj_AA.back());
	obj_AA.erase(--itr2(bk));
	//obj_AA.erase(--(--(obj_AA.end())));
	cout<<(obj_AA.size())<<endl;
	print_list2(obj_AA);
	// Test push_back
	Widget pbk1(7);
	obj_A.push_back(pbk1);
	Widget pbk2(19);
	obj_A.push_back(pbk2);
	print_list(obj_A);
	// Test pop_back
	obj_AA.pop_back();
	obj_AA.pop_back();
	print_list2(obj_AA);
	// Test swap
	riw2 obj_BB(std::move(obj_AA));
	obj_AA.swap(obj_BB);
	print_list2(obj_AA);
	print_list2(obj_BB);


	/*riw obj_D;
	std::vector<Widget> storage1;
	for(int i=4; i>=2; --i){
		storage1.push_back(Widget(i));
	}
	Widget* wp1 = storage1.data();
	itr ip1 = obj_D.begin();
	for(int i=0; i<(storage1.size()); ++i){
		obj_D.insert(ip1,*wp1);
		--ip1;
		++wp1;
	}
	print_list(obj_D);
	*/


	

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
