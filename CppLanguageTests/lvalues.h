#pragma once

#include <string>
#include <vector>

namespace lvalues {
	class MyVec {
		std::vector<std::string> vec;
	public:
		MyVec();
		std::string operator [](int pos);
	};

	int tests();
}