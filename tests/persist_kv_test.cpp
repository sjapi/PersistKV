#include "storage.h"
#include <cassert>
#include <iostream>

int main() {
	std::cout << "Running PersistKV tests..." << std::endl;

	put(42, 100);
	assert(get(42) == 100);
	del(42);
	return 0;
}
