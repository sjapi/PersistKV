#include "PersistKV.h"
#include <cassert>
#include <string>
#include <iostream>

int main() {
	std::cout << "Running PersistKV tests..." << std::endl;

	PersistKV<std::string, int>* db = new PersistKV<std::string, int>();

	assert(db->put("number", 1));
	assert(db->get("number").value_or(0) == 1);
	assert(db->del("number"));
	assert(db->size() == 0);
	return 0;
}
