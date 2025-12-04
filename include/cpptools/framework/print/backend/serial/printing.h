#pragma once

#include <iostream>
#include <string>
/*
namespace cpptools::framework::print {

	template<typename T, size_t N>
	void print(T(&t)[N], std::string delimiter = ", ") {
		using namespace std;
		int limiter = N - 1;
		int i = 0;
		for (i = 0; i < limiter; i++) {
			cout << t[i] << delimiter;
		}
		cout << t[i];
	}

	template<typename Container>
	void print(const Container& c, const std::string& delimiter = ", ") {
		using namespace std;
		size_t N = c.size();
		if (N == 0) return;

		for (size_t i = 0; i < N - 1; ++i)
			cout << c[i] << delimiter;
		cout << c[N - 1];
	}


	template<typename T, size_t N, size_t N2>
	void print(T(&t)[N][N2], std::string delimiter = ", ") {
		using namespace std;
		int n = N - 1;
		int n2 = N2 - 1;
		int i = 0;
		int i2 = 0;
		for (i; i < n; i++) {
			for (i2 = 0; i2 < n2; i2++) {
				cout << t[i][i2] << delimiter;
			}
			cout << t[i][i2] << "\n";
		}
		for (i2 = 0; i2 < n2; i2++) {
			cout << t[i][i2] << delimiter;
		}
		cout << t[i][i2];

	}



}

*/


#include <type_traits>
#include <iterator>

namespace cpptools::framework::print::backend::serial {

    // ============================================================
    // 工具：判断是否为 string
    // ============================================================
    template<typename T>
    struct is_string
        : std::is_same<typename std::decay<T>::type, std::string> {};

    // ============================================================
    // 工具：判断是否为 C 数组
    // ============================================================
    template<typename T>
    struct is_c_array
        : std::integral_constant<bool, std::is_array<T>::value> {};

    // ============================================================
    // 工具：检测是否有 begin/end → 检测是否为 STL 容器
    // ============================================================
    template<typename T>
    class has_begin_end {
        template<typename U>
        static auto test(int) -> decltype(
            std::begin(std::declval<U&>()),
            std::end(std::declval<U&>()),
            std::true_type{}
            );

        template<typename>
        static auto test(...) -> std::false_type;

    public:
        static constexpr bool value = decltype(test<T>(0))::value;
    };

    // ============================================================
    // 1. 叶子节点（非容器、非数组）
    // ============================================================
    template<typename T>
    typename std::enable_if<
        !has_begin_end<T>::value &&
        !is_c_array<T>::value &&
        !is_string<T>::value
    >::type
        print(const T& v, const std::string & = ", ")
    {
        std::cout << v;
    }


    // ============================================================
    // 2. 打印 string
    // ============================================================
    template<typename T>
    typename std::enable_if<is_string<T>::value>::type
        print(const T& s, const std::string & = ", ")
    {
        std::cout << "\"" << s << "\"";
    }


    // ============================================================
    // 3. 打印 STL 容器（vector, list, deque, set, unordered_set...）
    // ============================================================
    template<typename Container>
    typename std::enable_if<
        has_begin_end<Container>::value &&
        !is_string<Container>::value
    >::type
        print(const Container& c, const std::string& delimiter = ", ")
    {
        std::cout << "{";

        auto it = std::begin(c);
        auto end = std::end(c);

        if (it != end) {
            print(*it, delimiter);
            ++it;
        }

        for (; it != end; ++it) {
            std::cout << delimiter;
            print(*it, delimiter);
        }

        std::cout << "}";
    }


    // ============================================================
    // 4. 任意维度 C 数组（自动递归）
    // ============================================================
    template<typename T, size_t N>
    void print(const T(&arr)[N], const std::string& delimiter = ", ")
    {
        std::cout << "[";

        for (size_t i = 0; i < N; ++i) {
            print(arr[i], delimiter);
            if (i + 1 < N) std::cout << delimiter;
        }

        std::cout << "]";
    }

}

