#pragma once

#include <string>
#include <vector>

namespace memberref {
	class Class1 {
	public:
		std::string prop1;
		std::vector<std::string> vec1;
	};

	int memberRef();
}