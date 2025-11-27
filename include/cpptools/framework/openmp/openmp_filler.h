#pragma once

#include <iostream>

// update 
// openmp_setter.h

namespace cpptools::framework::openmp {

	template<typename T, size_t N>
	void fillWithIndex(T(&t)[N]) {
#pragma omp parallel for 
		for (int i = 0; i < N; i++) {
			t[i] = i;
		}
	}


}

