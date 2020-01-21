#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "memberref.h"

namespace memberref {
	std::string func1(std::string& arg) {
		return arg + "," + arg;
	}

	std::string join(const std::vector<std::string> vec) {
		std::string joined;
		//vec.insert(vec.begin(), "asd");
		for (int i = 0; i < vec.size(); i++) {
			joined += vec[i] + ",";
		}
		return joined;
	}

	int tests() {
		Class1 class1;
		class1.prop1 = "aer";

		std::cout << func1(class1.prop1) << std::endl;

		class1.vec1 = { "wer", "ete", "rty" };
		const std::vector<std::string> vec1c = const_cast<std::vector<std::string>&>(class1.vec1);

		std::cout << join(vec1c) << std::endl;

		std::cout << "end." << std::endl;
		return 0;
	}
}