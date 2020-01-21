#pragma once

#include <vector>
#include <array>
#include <concepts>

namespace Generics {
	static const int default_int;

	enum class ICAddResult {
		OK,
		TYPE_OVERFLOW
	};

	template <typename A, int AQ>
	class IC {
	private:
		std::array<A, AQ> a;
	public:
		IC() {
			a = {};
			for (int i = 0; i < AQ; ++i) {
				a[i] = default_int;
			}
		}
		template<typename A>
		ICAddResult Add(A x) {
			int i = 0;
			while (true) {
				if (a[i] != default_int) {
					++i;
					if (i + 1 > AQ) return ICAddResult::TYPE_OVERFLOW;
					continue;
				}
				break;
			}
			a[i] = x;
			return ICAddResult::OK;
		}
		typename const std::array<A, AQ> Get() {
			return a;
		}
	};

	template<typename T, typename A, typename B>
	concept IsAOrB = requires { std::is_same_v<T, A> || std::is_same_v<T, B>; };

	template <typename A, int AQ, typename B, int BQ>
	class IC2 {
	private:
		std::array<A, AQ> a;
		std::array<B, BQ> b;
	public:
		IC2() {
			// Initialize an array for each component of the collection, expressed as a type
			a = {};
			b = {};
			for (int i = 0; i < AQ; ++i) {
				a[i] = default_int;
			}
			for (int i = 0; i < BQ; ++i) {
				b[i] = default_int;
			}
		}
		template<typename T>
		requires IsAOrB<T, A, B>
		ICAddResult Add(T x) {
			// Evaluate whether T is A or B
			constexpr bool tIsA = std::is_same_v<T, A>;

			// Get a pointer to either a or b arrays, depending on T
			std::array<T, tIsA ? AQ : BQ>* arr;
			if constexpr (tIsA) arr = &a; else arr = &b;

			// Set the desired length of the array as the same as the class parameters AQ or BQ, 
			// depending on T
			constexpr int length = std::is_same_v<T, A> ? AQ : BQ;

			int i = 0;
			while (true) {
				// Find the first non-initialized position in the array and write the value
				// If we reach the end of the array without writing the value, return an error
				if (i + 1 > length) return ICAddResult::TYPE_OVERFLOW;
				if ((*arr)[i] != default_int) {
					++i;
					continue;
				}
				break;
			}
			(*arr)[i] = x;
			return ICAddResult::OK;
		}
		/*typename const std::array<A, AQ> GetA() {
			return a;
		}
		typename const std::array<B, BQ> GetB() {
			return b;
		}*/
	};

	int tests();
}