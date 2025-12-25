#pragma once

#include <iostream>
#include <string>
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

