#pragma once

#include <iostream>
#include <string>

namespace cpptools::framework::print {

	template<typename T, size_t N>
	void print(T(&t)[N], std::string delimiter = "\n") {
		using namespace std;
		for (T item : t) {
			std::cout << item << delimiter;

		}
	}

}

