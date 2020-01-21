#pragma once
#include <vector>

namespace ReturningRefs {
	class Object1 {
	public:
		Object1();
		Object1(const Object1& obj1); // Copy constructor
		std::vector<int> vec;
		~Object1();
	};

	int tests();
}