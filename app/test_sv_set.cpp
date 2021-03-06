#include"ra/sv_set.hpp"
#include<iostream>
#include<utility>
#include<functional>

int main(){
	using std::cout;
	using std::endl;
	using set = typename ra::container::sv_set<int>;
	using ourange = typename ra::container::sv_set<int>::ordered_and_unique_range;
	//using set = typename ra::container::sv_set<int, std::greater<int>>;
	//using ourange = typename ra::container::sv_set<int, std::greater<int>>::ordered_and_unique_range;
	// Test Default constructor
	set obj_A;
	// Test Move constructor and move assignment
	set obj_B(std::move(obj_A));
	set obj_C = std::move(obj_A);
	// Test Copy constructor and copy assignment
	set obj_D(obj_B);
	set obj_E = obj_D;
	// Test key compare function
	//cout<< (obj_E.key_comp()) << endl;
	// Test reserve
	obj_E.reserve(10);
	// Test insert
	obj_E.insert(7);
	obj_E.insert(2);
	obj_E.insert(5);
	set obj_EE(obj_E);
	// Test begin, finish,end,size,and capacity
	cout<<(*(obj_E.begin()))<<" "<<(*(obj_E.begin()+1))<<" "<<(*(obj_E.begin()+2))<<endl;
	cout<<(obj_E.size())<<" "<<(obj_E.capacity())<<endl;
	// Test shrink
	obj_E.shrink_to_fit();
	cout<<(*(obj_E.begin()))<<" "<<(*(obj_E.begin()+1))<<" "<<(*(obj_E.begin()+2))<<endl;
	cout<<(obj_E.size())<<" "<<(obj_E.capacity())<<endl;
	// Test find
	cout<<(*(obj_E.find(5)))<<endl;
	// Test clear
	obj_E.clear();
	cout<<(obj_E.size())<<" "<<(obj_E.capacity())<<endl;
	// Test constructor with range of values given
	int buf_1[] = {6,3,5,4,7,3,1,4,2,6,9};
	set obj_F(ourange(),buf_1,11);
	cout<<(obj_F.size())<<" "<<(obj_F.capacity())<<endl;
	for(int i=0; i<(obj_F.size()); ++i){
		cout<<(*(obj_F.begin()+i))<<" ";
	}
	cout<<endl;
	// Test constant find
	const set obj_G(obj_F);
	cout<<(*(obj_G.find(7)))<<endl;
	// Test erase
	cout<<(obj_F.size())<<endl;
	obj_F.erase(obj_F.find(3));
	for(int i=0; i<(obj_F.size()); ++i){
		cout<<(*(obj_F.begin()+i))<<" ";
	}
	cout<<endl;
	cout<<(obj_F.size())<<endl;
	// Test swap
	obj_F.swap(obj_EE);
	for(int i=0; i<(obj_EE.size()); ++i){
		cout<<(*(obj_EE.begin()+i))<<" ";
	}
	cout<<endl;
	for(int i=0; i<(obj_F.size()); ++i){
		cout<<(*(obj_F.begin()+i))<<" ";
	}
	cout<<endl;





}
