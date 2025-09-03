#include "Serializer.h"

#include <string>
#include <cassert>

int main() {
	/* Int */
	int a1 = 42;
	std::string s_a = PersistKVSerializer<int>::serialize(a1);
	int a2 = PersistKVSerializer<int>::deserialize(s_a);
	assert(a1 == a2);

	/* Double */
	double a3 = 3.14;
	s_a = PersistKVSerializer<double>::serialize(a3);
	double a4 = PersistKVSerializer<double>::deserialize(s_a);
	assert(a3 == a4);

	/* String */
	std::string a5 = "NVIDIA's Nucleus team is the best";
	s_a = PersistKVSerializer<std::string>::serialize(a5);
	std::string a6 = PersistKVSerializer<std::string>::deserialize(s_a);
	assert(a5 == a6);

	/* Bool */
	bool a7 = false;
	s_a = PersistKVSerializer<bool>::serialize(a7);
	double a8 = PersistKVSerializer<double>::deserialize(s_a);
	assert(a7 == a8);

	return 0;
}
