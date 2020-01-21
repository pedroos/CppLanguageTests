#include "generics.h"
#include <iostream>
#include <assert.h>

namespace Generics {
	int tests() {
		IC<int, 1> ic;
		auto res = ic.Add(1);
		assert(res == ICAddResult::OK);
		res = ic.Add(2);
		assert(res == ICAddResult::TYPE_OVERFLOW);
		auto a = ic.Get();
		for (auto it = a.begin(); it != a.end(); ++it)
			std::cout << *it << std::endl;

		IC2<int, 1, double, 2> ic2;
		ic2.Add<int>(1);
		//ic2.Add<int>(1.2);
		ic2.Add<double>(2.3);
		//res = ic2.Add<double>(2);
		//assert(res == ICAddResult::TYPE_OVERFLOW);

		return 0;
	}
}