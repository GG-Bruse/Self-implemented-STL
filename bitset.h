#pragma once
#include "vector.hpp"

namespace bjy {
	template<size_t N>
	class bitset {
	public:
		bitset() {
			if (N % 8 == 0) _bits.resize(N / 8, 0);
			else _bits.resize(N / 8 + 1, 0);
		}
		void set(size_t which) {
			size_t i = which / 8, j = which % 8;
			_bits[i] |= (1 << j);
		}

		void reset(size_t which) {
			size_t i = which / 8, j = which % 8;
			_bits[i] &= ~(1 << j);
		}

		bool test(size_t which)const {
			size_t i = which / 8, j = which % 8;
			return _bits[i] & (1 << j);
		}
	private:
		vector<char> _bits;
	};
}