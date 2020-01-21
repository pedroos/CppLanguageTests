#include "pch.h"
#include <iostream>
#include "lvalues.h"
#include <vector>

namespace lvalues {
	MyVec::MyVec() {
		vec.push_back("asd");
		vec.push_back("wer");
		vec.push_back("ert");
	}

	std::string MyVec::operator [](int pos){
		return vec[pos];
	}

	int& dosom() {
		int i = 1;
		return i;
	}

	int tests() {
		// Igualar um lvalue a um lvalue.
		int& i = dosom();

		std::cout << &i << "," << std::endl;

		MyVec myVec;
		std::cout << myVec[0] << std::endl;

		return 0;
	}
}