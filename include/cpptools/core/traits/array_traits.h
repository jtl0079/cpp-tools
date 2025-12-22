#pragma once

#include <cstddef>


namespace cpptools::core::traits {

    // --- Detect array extent ---
    template<typename T>
    struct array_traits;

    template<typename T, size_t N>
    struct array_traits<T[N]> {
        using element_type = T;
        static constexpr size_t dim = array_traits<T>::dim + 1;
    };

    template<typename T>
    struct array_traits {
        static constexpr size_t dim = 0;
    };


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


} // namespace cpptools::core::traits
