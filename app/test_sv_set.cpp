#include"ra/sv_set.hpp"
#include<iostream>
#include<utility>

int main(){
	using std::cout;
	using std::endl;
	using set = typename ra::container::sv_set<int>;
	set obj_A;
	set obj_B(std::move(obj_A));
	set obj_C = std::move(obj_A);
}
