#include "pch.h"
#include <memory>
#include <vector>
#include <iostream>
#include "allocinfunc.h"

namespace AllocInFunc {
	// Wrong, although the syntax is better
	std::unique_ptr<std::vector<int>> allocInFuncNoPointerBadAlloc() {
		std::vector<int> vec;
		vec.push_back(1);

		return std::unique_ptr<std::vector<int>>(&vec);
	}

	// Uglier, but correct
	std::unique_ptr<std::vector<int>> allocInFunc() {
		std::vector<int>* vec = new std::vector<int>();
		vec->push_back(1);

		return std::unique_ptr<std::vector<int>>(vec);
	}

	// Clear, but may copy
	std::vector<int> allocInFuncCopy() {
		std::vector<int> vec;
		vec.push_back(1);

		return vec;
	}

	SmartPtrContainer::SmartPtrContainer(std::vector<int>* vecRef) {
		this->vecRef = std::unique_ptr<std::vector<int>>(vecRef);
		std::cout << "	Constructed SmartPtrContainer with vec of size " << vecRef->size() << std::endl;
	}

	SmartPtrContainer::~SmartPtrContainer() {
		vecRef.reset();
		std::cout << "	Destructor: deleted SmartPtrContainer vec" << std::endl;
	}

	CopyContainer::CopyContainer(std::vector<int> vecCopy) {
		this->vecCopy = vecCopy;
	}

	CopyContainer::CopyContainer(const CopyContainer& copyContainer) {
		std::cout << "	Copy-construct CopyContainer from reference with vec size" <<
			copyContainer.vecCopy.size() << std::endl;
		this->vecCopy = copyContainer.vecCopy;
	}

	SharedValueContainer::SharedValueContainer() {}

	void SharedValueContainer::open() {
		database = "Database name";
	}

	void SharedValueContainer::accessValue() {
		std::cout << " Database is " << database;
	}

	std::unique_ptr<std::vector<std::string>> SharedValueContainer::getSomeValue() {
		//std::vector<std::string> v = std::vector<std::string>();
		std::vector<std::string> *v = new std::vector<std::string>();
		v->push_back(database);
		return std::unique_ptr<std::vector<std::string>>(v);
		//return std::unique_ptr<std::vector<int>>(&someValue);
	}

	// Wrong
	std::unique_ptr<SmartPtrContainer> allocInFuncObjNoPointerCrash() {
		std::vector<int>* vec = new std::vector<int>();
		vec->push_back(1);

		SmartPtrContainer container(vec);
		return std::unique_ptr<SmartPtrContainer>(&container);
	}

	// Correct
	std::unique_ptr<SmartPtrContainer> allocInFuncObj() {
		std::vector<int>* vec = new std::vector<int>();
		vec->push_back(1);

		SmartPtrContainer* container = new SmartPtrContainer(vec);
		return std::unique_ptr<SmartPtrContainer>(container);
	}

	// Clear, may copy
	CopyContainer allocInFuncObjCopy() {
		std::vector<int> vec;
		vec.push_back(1);

		CopyContainer container(vec);
		return container;
	}

	// Substitute reference value
	void allocInFuncSubstituteReference(std::vector<int>& vec) {
		std::vector<int> newVec;
		newVec.push_back(2);
		vec = newVec;
	}

	// Move value
	void allocInFuncMoveValue(std::vector<int>& vec) {
		std::vector<int> newVec;
		newVec.push_back(2);
		vec = std::move(newVec);
	}

	int tests() {
		{
			std::cout << "Func alloc (correct)" << std::endl;
			auto alloced2 = allocInFunc();
			std::vector<int>* vec2 = alloced2.get();
			std::cout << "	vec first item: " << ((*vec2)[0] == 1) << std::endl;
			//delete(vec2);
		}

		/*{ // crashes
			std::cout << "Func alloc (wrong)" << std::endl;
			auto alloced = allocInFuncNoPointerBadAlloc();
			try {
				std::vector<int> vec = *alloced.get();
			}
			catch (std::bad_alloc) {
				std::cout << "	bad_alloc catched." << std::endl;
			}
		}*/

		// Pattern to return allocated object(s) from function
		{
			std::cout << "Pattern (correct)" << std::endl;
			auto container = allocInFuncObj();
			auto containerVec = container.get()->vecRef.get();
			std::cout << "	container vec first item: " << (*containerVec)[0] << std::endl;
		}

		/*{ // crashes
			std::cout << "Pattern (wrong)" << std::endl;
			try {
				auto container = allocInFuncObjNoPointerCrash();
				auto containerVec = container.get()->vecRef.get();
				std::cout << "	container vec first item: " << (*containerVec)[0];
			}
			catch (...) {
				std::cout << "	generic exception catched." << std::endl;
			}
		}*/

		// Pattern to return allocated object(s) from function
		{
			std::cout << "Pattern (correct and clear but copy)" << std::endl;
			CopyContainer container = allocInFuncObjCopy();
			std::cout << "	container vec first item: " << container.vecCopy[0] << std::endl;
		}

		// Substitute reference value
		{
			std::cout << "Pattern (substitute reference)" << std::endl;
			std::vector<int> vec;
			vec.push_back(1);
			allocInFuncSubstituteReference(vec);
			std::cout << "	substituted container vec first item: " << vec[0] << std::endl;
		}

		// Move value
		{
			std::cout << "Pattern (move value)" << std::endl;
			std::vector<int> vec;
			vec.push_back(1);
			allocInFuncMoveValue(vec);
			std::cout << "	substituted container vec first item: " << vec[0] << std::endl;
		}

		// Class value in smart pointer survives subfunction call
		{
			SharedValueContainer svc;
			svc.open();
			std::unique_ptr<std::vector<std::string>> ptr = svc.getSomeValue();
			std::cout << "Class value size: " << ptr.get()->at(0);
			svc.accessValue();
			std::cout << "Class value size 2: " << ptr.get()->at(0);
		}

		return 0;
	}
}