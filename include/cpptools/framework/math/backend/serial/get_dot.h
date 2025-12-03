#pragma once


namespace cpptools::framework::math::backend::serial {



    // ---------------------------------------------------------
    // 多向量单个 index 处的乘积
    // ---------------------------------------------------------
    template<typename T, size_t N, typename... Vecs>
    T multiply_at(size_t i, const T(&first)[N], const Vecs(&... vecs)[N]) {
        return (first[i] * ... * vecs[i]); // fold expression
    }

    // ---------------------------------------------------------
    // 主函数：接收任意数量 vector
    // ---------------------------------------------------------
    template<typename T, size_t N, typename... Vecs>
    T get_dot(const T(&first)[N], const Vecs(&... vecs)[N]) {
        // 静态断言：保证所有数组尺寸一致
        static_assert((std::is_same_v<const T(&)[N], const Vecs(&)[N]> && ...),
            "All vectors must be same type and size");

        T sum{};
        for (size_t i = 0; i < N; i++) {
            sum += multiply_at(i, first, vecs...);
        }
        return sum;
    }

}