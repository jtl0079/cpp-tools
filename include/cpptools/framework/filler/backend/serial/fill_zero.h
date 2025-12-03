#pragma once

namespace cpptools::framework::filler::backend::serial {

    template<class T, size_t N>
    void fill_zero_impl(T(&arr)[N]) {
        for (auto& x : arr) {
            x = T{};
        }
    }

    // 基础版本：单个二维数组
    template<typename T, size_t M, size_t N>
    void fill_zero_impl(T(&t)[M][N]) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                t[i][j] = T{};
            }
        }
    }

    // 可变参数模板：接收多个数组
    template<typename... Arrays>
    void fill_zero(Arrays&... arrays) {
        (fill_zero_impl(arrays), ...);  // C++17 fold expression
    }

}