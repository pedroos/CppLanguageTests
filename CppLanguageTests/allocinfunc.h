#pragma once

#include <memory>
#include <vector>

namespace AllocInFunc {
	std::unique_ptr<std::vector<int>> allocInFuncNoPointerBadAlloc();
	std::unique_ptr<std::vector<int>> allocInFunc();

	class SmartPtrContainer {
	public:
		SmartPtrContainer(std::vector<int>* vecRef);
		~SmartPtrContainer();
		std::unique_ptr<std::vector<int>> vecRef;
	};

	class CopyContainer {
	public:
		CopyContainer(std::vector<int> vecCopy);
		CopyContainer(const CopyContainer& copyContainer);
		CopyContainer(CopyContainer&& copyContainer) = default;
		std::vector<int> vecCopy;
	};

	class SharedValueContainer {
	private:
		std::string database;
		std::vector<std::string> someValue;
	public:
		void open();
		SharedValueContainer();
		std::unique_ptr<std::vector<std::string>> getSomeValue();
		void accessValue();
	};

	int tests();
}