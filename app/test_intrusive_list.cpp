#include "ra/intrusive_list.hpp"

namespace ri = ra::intrusive;

struct Widget {
	Widget(int value_) : value(value_) {}
	int value;
	ri::list_hook hook;
};

int main() {
	std::vector<Widget> storage;
	storage.push_back(Widget(42));
	ri::list<Widget, &Widget::hook> values;
	for (auto&& i : storage) {
		values.push_back(i);
	}
	values.clear();
}