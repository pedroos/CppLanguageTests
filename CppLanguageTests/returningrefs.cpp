#include "pch.h"
#include <vector>
#include <string>
#include "returningrefs.h"
#include <iostream>

namespace ReturningRefs {
	
	Object1::Object1() {
		vec.push_back(1);
	}

	Object1::Object1(const Object1& obj1) { // Copy constructor
		std::cout << "	Object1 copy constructor called. Will copy " << 
			obj1.vec.size() << " vec elements to a new object" << std::endl;
		for (int i = 0; i < obj1.vec.size(); ++i)
			vec.push_back(obj1.vec[i]);
	}

	Object1::~Object1() {
		std::cout << "	Object1 being destructed." << std::endl;
	}

	// Copy on return.
	Object1 copyFun() {
		Object1 obj1;
		return obj1;
	}

	// No copy, but temporary (wrong).
	Object1& refFun() {
		Object1 obj1;
		return obj1;
	}

	// Correct, no copy
	std::unique_ptr<Object1> ptrFun() {
		Object1 *obj1 = new Object1();
		return std::unique_ptr<Object1>(obj1);
	}

	int tests() {
		Object1 copyFun();

		// This will crash
		//Object1& obj1 = refFun();
		//std::cout << "    wrong obj1: vec first element is " << obj1.vec[0] << std::endl;

		auto obj2 = ptrFun();
		std::cout << "    obj2: vec first element is " << obj2->vec[0] << std::endl;

		return 0;
	}
}