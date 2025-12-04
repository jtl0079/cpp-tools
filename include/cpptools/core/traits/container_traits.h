#pragma once


#pragma once
#include <cstddef>

namespace cpptools::core::traits {

    template<class Container>
    constexpr size_t size(const Container& c) {
        return c.size();
    }

    template<class T, size_t N>
    constexpr size_t size(const T(&)[N]) {
        return N;
    }

    template<class Container>
    constexpr auto& get(Container& c, size_t i) {
        return c[i];
    }

    template<class T, size_t N>
    constexpr T& get(T(&arr)[N], size_t i) {
        return arr[i];
    }

}
